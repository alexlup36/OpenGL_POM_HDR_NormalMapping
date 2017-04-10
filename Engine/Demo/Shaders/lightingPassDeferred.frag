#version 450 core

// -------------------------------------------------------

#define MAX_POINT_LIGHTS 2

// -------------------------------------------------------

struct DirectionalLight
{
    vec3 lightDirection;
	vec3 ambientLight;
	vec3 diffuseLight;
	vec3 specularLight;
	float specularIntensity;
};

struct PointLight
{
    vec3 lightPosition;
	vec3 ambientLight;
	vec3 diffuseLight;
	vec3 specularLight;
	float specularIntensity;
};

struct Material
{
	vec3 vMatEmission;
	vec3 vMatAmbient;
	vec3 vMatDiffuse;
	vec3 vMatSpecular;
	float fMatShineness;
};

// -------------------------------------------------------

in vec2 TexCoord;

// -------------------------------------------------------

// GBuffer uniforms
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D gAlbedoSpec2;
uniform sampler2D gNormal2;

uniform DirectionalLight dirLight;
uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform Material material;
uniform vec3 eyePosW;

// -------------------------------------------------------

// Output data
out vec4 color;

// -------------------------------------------------------

vec4 phongShading(vec3 positionW, vec3 normal, vec3 color, float specularIntensity)
{
	// Calculate ambient component
	vec3 ambientComponent = dirLight.ambientLight;
	
	// Calculate diffuse component
	vec3 lightDir = normalize(dirLight.lightDirection - positionW);
	float diffuse = max(dot(normal, lightDir), 0.0f);
	vec3 diffuseComponent = diffuse * dirLight.diffuseLight;
	
	// Calculate specular component
	vec3 viewDirection = normalize(eyePosW - positionW);
	vec3 reflectionDirection = reflect(-lightDir, normal);
	float specular = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 64.0f);
	vec3 specularComponent = specular * dirLight.specularLight * dirLight.specularIntensity;
	
	return vec4(ambientComponent + diffuseComponent, 1.0f) * vec4(color, 1.0f) + vec4(specularComponent, 1.0f);
}

// -------------------------------------------------------

vec4 blinnPhongShading(vec3 positionW, vec3 normal, vec3 color, float specularIntensity)
{
	// Calculate ambient component ---------------------------------------------------------------
	vec3 ambientComponent = dirLight.ambientLight;
	
	// Calculate diffuse component ---------------------------------------------------------------
	vec3 diffuseComponent;
	vec3 lightDir = normalize(-dirLight.lightDirection);
	
	float diffuse = max(dot(normal, lightDir), 0.0f);
	diffuseComponent = diffuse * dirLight.diffuseLight;
	
	// Calculate specular component --------------------------------------------------------------
	vec3 viewDirection = normalize(eyePosW - positionW);
	vec3 halfWayDirection = normalize(lightDir + viewDirection);
	float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.fMatShineness);
	vec3 specularComponent = specular * dirLight.specularLight * dirLight.specularIntensity;
	
	return vec4(ambientComponent + diffuseComponent, 1.0f) * vec4(color, 1.0f) + vec4(specularComponent, 1.0f);
}

// -------------------------------------------------------

vec4 blinnPhongShadingPoint(vec3 positionW, vec3 normal, vec3 color, float specularIntensity)
{
	vec3 totalAmbient = vec3(0.0f, 0.0f, 0.0f);
	vec3 totalDiffuse = vec3(0.0f, 0.0f, 0.0f);
	vec3 totalSpecular = vec3(0.0f, 0.0f, 0.0f);

	float kc = 1.0f;
	float kl = 0.027f;
	float kq = 0.0028f;

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		// Calculate ambient component ---------------------------------------------------------------
		vec3 ambientComponent = pointLight[i].ambientLight * material.vMatAmbient;
		
		// Calculate diffuse component ---------------------------------------------------------------
		vec3 diffuseComponent, lightVector;
		lightVector = (pointLight[i].lightPosition - positionW);
		
		
		float distance = length(lightVector);
		vec3 lightDir = normalize(lightVector);
		float diffuse = max(dot(normal, lightDir), 0.0f);
		diffuseComponent = diffuse * pointLight[i].diffuseLight * material.vMatDiffuse;
		
		// Calculate specular component --------------------------------------------------------------
		vec3 viewDirection = normalize(eyePosW - positionW);
		vec3 halfWayDirection = normalize(lightDir + viewDirection);
		float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.fMatShineness);
		vec3 specularComponent = specular * pointLight[i].specularLight * 
			material.vMatSpecular * pointLight[i].specularIntensity;
		
		// Calculate the attenuation
		float attenuation = 1.0f / (kc + kl * distance + kq * (distance * distance));
		
		totalAmbient += ambientComponent * attenuation;
		totalDiffuse += diffuseComponent * attenuation;
		totalSpecular += specularComponent * attenuation;
	}
	
	return vec4(totalAmbient + totalDiffuse, 1.0f) * vec4(color, 1.0f) + vec4(totalSpecular, 1.0f);
}

// -------------------------------------------------------

void main()
{
	// Retrieve data from gbuffer
    vec3 FragPos	= texture(gPosition, TexCoord).rgb;
    vec3 Normal		= texture(gNormal, TexCoord).rgb;
    vec3 Normal2	= texture(gNormal2, TexCoord).rgb;
    vec3 Diffuse	= texture(gAlbedoSpec, TexCoord).rgb;
    vec3 Diffuse2	= texture(gAlbedoSpec2, TexCoord).rgb;
    float Specular	= texture(gAlbedoSpec, TexCoord).a;

    vec3 normalResult = 0.5f * (Normal + Normal2);
    vec3 red = vec3(1.0f, 0.0f, 0.0f);
    vec3 zero = vec3(0.0f, 0.0f, 0.0f);

	color = blinnPhongShading(FragPos, normalResult, Diffuse, Specular) * 0.5f + blinnPhongShading(FragPos, normalResult, Diffuse2, Specular) * 0.5f;
	color = saturate(blinnPhongShading(FragPos, normalResult, Diffuse, Specular) + blinnPhongShading(FragPos, normalResult, Diffuse2, Specular));
}

// -------------------------------------------------------