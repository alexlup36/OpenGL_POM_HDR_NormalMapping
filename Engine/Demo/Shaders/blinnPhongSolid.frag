#version 430

// ----------------------------------------------------------------------------
// Constants

#define MAX_POINT_LIGHTS 10
#define MAX_DIRECTIONAL_LIGHTS 10
#define MAX_SPOT_LIGHTS 10 

// ----------------------------------------------------------------------------
// Struct definition

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
	vec3 attenuation;
};

struct SpotLight
{
	vec3 lightPosition;
	vec3 ambientLight;
	vec3 diffuseLight;
	vec3 specularLight;
	vec3 spotLightDirection;
	float spotLightExponent;
	float spotLightCutoff;
	float spotLightCosCutoff;
};

struct Material
{
	vec3 vMatEmission;
	vec3 vMatAmbient;
	vec3 vMatDiffuse;
	vec3 vMatSpecular;
	float fMatShineness;
};

// ----------------------------------------------------------------------------
// Uniforms

uniform DirectionalLight dirLight[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform SpotLight spotLight[MAX_SPOT_LIGHTS];
uniform Material material;
uniform vec3 eyePosW;
uniform int dirLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

// ----------------------------------------------------------------------------
// Input

in vec2 texCoord;
in vec3 vertexW;
in vec3 normalW;

// ----------------------------------------------------------------------------
// Output

out vec4 color;

// ----------------------------------------------------------------------------

vec4 blinnPhongShadingPoint(vec3 normal)
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	
	float kc = 1.0f;
	float kl = 0.027f;
	float kq = 0.0028f;

	for (int i = 0; i < pointLightCount; i++)
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
		float attenuation = 1.0f / (pointLight[i].attenuation.z + pointLight[i].attenuation.y * distance + pointLight[i].attenuation.x * (distance * distance));
		
		color += (ambientComponent + diffuseComponent + specularComponent) * attenuation;
	}
	
	return vec4(color, 1.0f);
}

// ----------------------------------------------------------------------------

vec4 blinnPhongShadingDir(vec3 normal)
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < dirLightCount; i++)
	{
		// Calculate ambient component ---------------------------------------------------------------
		vec3 ambientComponent = dirLight[i].ambientLight * material.vMatAmbient;
		
		// Calculate diffuse component ---------------------------------------------------------------
		vec3 diffuseComponent;
		vec3 lightDir = normalize(-dirLight[i].lightDirection);
		float diffuse = max(dot(normal, lightDir), 0.0f);
		diffuseComponent = diffuse * dirLight[i].diffuseLight * material.vMatDiffuse;
		
		// Calculate specular component --------------------------------------------------------------
		vec3 viewDirection = normalize(eyePosW - vertexW);
		vec3 halfWayDirection = normalize(lightDir + viewDirection);
		float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.fMatShineness);
		vec3 specularComponent = specular * dirLight[i].specularLight * material.vMatSpecular;

		color += ambientComponent + diffuseComponent + specularComponent;
	}
	
	return vec4(color, 1.0f);
}

// ----------------------------------------------------------------------------

vec4 blinnPhongShadingSpot(vec3 normal)
{
	// TODO
	return vec4(0.0f, 0.0f, 0.0f, 1.0f);
}


// ----------------------------------------------------------------------------

void main()
{
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Calculate lighting using the Phong lighting model

	// Directional lights
	for (int dirLightIndex = 0; dirLightIndex < dirLightCount; ++dirLightIndex)
	{
		color += blinnPhongShadingDir(normalW);
	}
	
	// Point lights
	for (int pointLightIndex = 0; pointLightIndex < pointLightCount; ++pointLightIndex)
	{
		color += blinnPhongShadingPoint(normalW);
	}

	// Spot lights
	for (int spotLightIndex = 0; spotLightIndex < spotLightCount; ++spotLightIndex)
	{
		color += blinnPhongShadingSpot(normalW);
	}

	color.w = 0.6f;
}