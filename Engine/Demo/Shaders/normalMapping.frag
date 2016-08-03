#version 450

#define MAX_POINT_LIGHTS 2

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

uniform sampler2D diffuseSampler;
uniform sampler2D normalSampler;
uniform sampler2D displacementSampler;
uniform float dispMapScale;
uniform DirectionalLight dirLight;
uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform Material material;
uniform float gamma;
uniform vec3 eyePosW;

in vec2 texCoord;
in vec3 vertexW;
in mat3 TBNMatrix;
in vec3 normalW;

out vec4 color;

// ----------------------------------------------------------------------------

vec4 phongShading(vec3 normal, vec4 color)
{
	// Calculate ambient component
	vec3 ambientComponent = dirLight.ambientLight;
	
	// Calculate diffuse component
	vec3 lightDir = normalize(dirLight.lightDirection - vertexW);
	float diffuse = max(dot(normal, lightDir), 0.0f);
	vec3 diffuseComponent = diffuse * dirLight.diffuseLight;
	
	// Calculate specular component
	vec3 viewDirection = normalize(eyePosW - vertexW);
	vec3 reflectionDirection = reflect(-lightDir, normal);
	float specular = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.fMatShineness);
	vec3 specularComponent = specular * dirLight.specularLight * dirLight.specularIntensity;
	
	return vec4(ambientComponent + diffuseComponent, 1.0f) * color + vec4(specularComponent, 1.0f);
}

// ----------------------------------------------------------------------------

vec4 blinnPhongShadingPoint(vec3 normal, vec4 color)
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
		lightVector = (pointLight[i].lightPosition - vertexW);
		
		
		float distance = length(lightVector);
		vec3 lightDir = normalize(lightVector);
		float diffuse = max(dot(normal, lightDir), 0.0f);
		diffuseComponent = diffuse * pointLight[i].diffuseLight * material.vMatDiffuse;
		
		// Calculate specular component --------------------------------------------------------------
		vec3 viewDirection = normalize(eyePosW - vertexW);
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
	
	return vec4(totalAmbient + totalDiffuse, 1.0f) * color + vec4(totalSpecular, 1.0f);
}

// ----------------------------------------------------------------------------

vec4 blinnPhongShading(vec3 normal, vec4 color)
{
	float sphericalLightRadius = 10.0f;
	float influenceDistance = 5.0f;

	// Calculate ambient component ---------------------------------------------------------------
	vec3 ambientComponent = dirLight.ambientLight;
	
	// Calculate diffuse component ---------------------------------------------------------------
	vec3 diffuseComponent;
	vec3 lightDir = normalize(-dirLight.lightDirection);
	
	float diffuse = max(dot(normal, lightDir), 0.0f);
	diffuseComponent = diffuse * dirLight.diffuseLight;
	
	// Calculate specular component --------------------------------------------------------------
	vec3 viewDirection = normalize(eyePosW - vertexW);
	vec3 halfWayDirection = normalize(lightDir + viewDirection);
	float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.fMatShineness);
	vec3 specularComponent = specular * dirLight.specularLight * dirLight.specularIntensity;
	
	return vec4(ambientComponent + diffuseComponent, 1.0f) * color + vec4(specularComponent, 1.0f);
}

// ----------------------------------------------------------------------------

vec2 ParallaxMapping(vec2 texCoord, vec3 viewDirection)
{
	// Number of depth layers
	const float minLayerCount = 8;
	const float maxLayerCount = 32;
	float layerCount = mix(maxLayerCount, minLayerCount, abs(dot(vec3(0.0f, 0.0f, 1.0f), viewDirection)));
	// Calculate the size of each layer
	float layerDepth = 1.0f / layerCount;
	// Depth of the current layer
	float currentLayerDepth = 0.0f;
	// Texture offset for each depth layer
	vec2 p = viewDirection.xy * dispMapScale;
	vec2 deltaTexCoords = p / layerCount;
	// Set initial values
	vec2 currentTexCoord = texCoord;
	float currentDepthMapValue = texture(displacementSampler, currentTexCoord).r;
	
	while (currentLayerDepth < currentDepthMapValue)
	{
		// Adjust the texture coordinates for the current depth values
		currentTexCoord -= deltaTexCoords;
		
		// Get the depth map value at the current texture coordinate
		currentDepthMapValue = texture(displacementSampler, currentTexCoord).r;
	
		// Increment the current layer depth
		currentLayerDepth += layerDepth;
	}
	
	// Get the previous tex coordinate
	vec2 prevTexCoord = currentTexCoord + deltaTexCoords;
	// Get the depth value after and before the collision
	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(displacementSampler, prevTexCoord).r - currentLayerDepth + layerDepth;
	
	// Do the interpolation
	float weight = afterDepth / (afterDepth - beforeDepth);
	
	return prevTexCoord * weight + currentTexCoord * (1.0f - weight);
}

// ----------------------------------------------------------------------------

void main()
{
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Parallax displacement mapping
	vec3 viewDirectionTangent = normalize(TBNMatrix * (eyePosW - vertexW));
	vec2 texCoordParallax = ParallaxMapping(texCoord, viewDirectionTangent);
	if (texCoordParallax.x > 1.0f || texCoordParallax.y > 1.0f || texCoordParallax.x < 0.0f || texCoordParallax.y < 0.0f)
	{
		discard;
	}
	
	// Sample the diffuse and normal textures
	vec4 diffuseColor = texture(diffuseSampler, texCoordParallax);
	vec3 normal = normalize(TBNMatrix * (2.0f * texture(normalSampler, texCoordParallax).xyz - 1.0f));
	
	// Calculate lighting using the Phong model texture
	color += blinnPhongShading(normal, diffuseColor);
	color += blinnPhongShadingPoint(normal, diffuseColor);
}