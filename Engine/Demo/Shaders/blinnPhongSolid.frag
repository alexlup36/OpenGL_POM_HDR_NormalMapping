#version 430

#define MAX_POINT_LIGHTS 2

struct DirectionalLight
{
    vec3 lightDirection;
	vec3 ambientLight;
	vec3 diffuseLight;
	vec3 specularLight;
};

struct PointLight
{
    vec3 lightPosition;
	vec3 ambientLight;
	vec3 diffuseLight;
	vec3 specularLight;
};

struct Material
{
	vec3 vMatEmission;
	vec3 vMatAmbient;
	vec3 vMatDiffuse;
	vec3 vMatSpecular;
	float fMatShineness;
};

uniform DirectionalLight dirLight;
uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform Material material;
uniform vec3 eyePosW;
uniform float gamma;

in vec2 texCoord;
in vec3 vertexW;
in vec3 normalW;

out vec4 color;

// ----------------------------------------------------------------------------

vec4 blinnPhongShadingPoint(vec3 normal)
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	
	float kc = 1.0f;
	float kl = 0.027f;
	float kq = 0.0028f;

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		// Calculate ambient component ---------------------------------------------------------------
		vec3 ambientComponent = pointLight[i].ambientLight * material.vMatAmbient;
		
		// Calculate diffuse component ---------------------------------------------------------------
		vec3 diffuseComponent, lightVector;
		lightVector = pointLight[i].lightPosition - vertexW;
		
		float distance = length(lightVector);
		vec3 lightDir = normalize(lightVector);
		float diffuse = max(dot(normal, lightDir), 0.0f);
		diffuseComponent = diffuse * pointLight[i].diffuseLight * material.vMatDiffuse;
		
		// Calculate specular component --------------------------------------------------------------
		vec3 viewDirection = normalize(eyePosW - vertexW);
		vec3 halfWayDirection = normalize(lightDir + viewDirection);
		float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.fMatShineness);
		vec3 specularComponent = specular * pointLight[i].specularLight * material.vMatSpecular;
		
		// Calculate the attenuation
		float attenuation = 1.0f / (kc + kl * distance + kq * (distance * distance));
		
		color += (ambientComponent + diffuseComponent + specularComponent) * attenuation;
	}
	
	return vec4(color, 1.0f);
}

// ----------------------------------------------------------------------------

vec4 blinnPhongShading(vec3 normal)
{
	// Calculate ambient component ---------------------------------------------------------------
	vec3 ambientComponent = dirLight.ambientLight * material.vMatAmbient;
	
	// Calculate diffuse component ---------------------------------------------------------------
	vec3 diffuseComponent;
	vec3 lightDir = normalize(-dirLight.lightDirection);
	float diffuse = max(dot(normal, lightDir), 0.0f);
	diffuseComponent = diffuse * dirLight.diffuseLight * material.vMatDiffuse;
	
	// Calculate specular component --------------------------------------------------------------
	vec3 viewDirection = normalize(eyePosW - vertexW);
	vec3 halfWayDirection = normalize(lightDir + viewDirection);
	float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.fMatShineness);
	vec3 specularComponent = specular * dirLight.specularLight * material.vMatSpecular;
	
	return vec4(ambientComponent + diffuseComponent + specularComponent, 1.0f);
}

// ----------------------------------------------------------------------------

void main()
{
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Calculate lighting using the Phong model texture
	color += blinnPhongShading(normalW);
	color += blinnPhongShadingPoint(normalW);
}