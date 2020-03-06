#version 430

// ------------------------------------------------------------------
// ------------------------------------------------------------------

#define PI 3.1415926535897932384626433832795
#define PI_2 1.57079632679489661923
#define PI_4 0.785398163397448309616

#define MAX_POINT_LIGHTS 10
#define MAX_DIRECTIONAL_LIGHTS 10
#define MAX_SPOT_LIGHTS 10 

// ----------------------------------------------------------------------------
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

struct PBRMaterial
{
	vec3 albedo;
	float metallic;
	float roughness;
	float ao;
};

// ------------------------------------------------------------------
// ------------------------------------------------------------------

// Uniforms

// Samplers
uniform DirectionalLight dirLight[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLight[MAX_POINT_LIGHTS];
uniform SpotLight spotLight[MAX_SPOT_LIGHTS];
uniform int dirLightCount;
uniform int pointLightCount;
uniform int spotLightCount;

// Camera
uniform vec3 eyePosW;
// Light
uniform vec4 lightPosW;

// Samplers
uniform sampler2D diffuseSampler;
uniform sampler2D normalSampler;
uniform sampler2D displacementSampler;
// x - roughness, y = metallic, z = ambient occlusion
uniform sampler2D pbrSampler;
uniform float dispMapScale;

// Tone mapping
uniform float gamma;

// ------------------------------------------------------------------
// ------------------------------------------------------------------

// Normal distribution function - Trwobridge-Reitz GGX
float ndf_ggxtr(vec3 normal, vec3 halfway, float roughness)
{
	float roughness2 = roughness * roughness;
	float roughness4 = roughness2 * roughness2;
	float nDoth = dot(normal, halfway);
	float nDoth2 = nDoth * nDoth;

	float nom = roughness4;
	float denom = nDoth2 * (roughness4 - 1.0f) + 1.0f;
	denom = PI * denom * denom;

	return nom / denom;
}

// ------------------------------------------------------------------

// Roughness remap function for dielectrics
float roughnessRemapDielectrics(float roughness)
{
	float r = roughness + 1.0f;
	return (r * r) / 8.0f;
}

// ------------------------------------------------------------------

// Roughness remap function for conductors
float roughnessRemapConductors(float roughness)
{
	return (roughness * roughness) / 2.0f;
}

// ------------------------------------------------------------------

// Geometry function - Smith's method using SchlickGGX
float gf_schlickggx(float dot, float remapRoughness)
{
	float nom = dot;
	float denom = dot * (1.0f - remapRoughness) + remapRoughness;

	return nom / denom;
}

// ------------------------------------------------------------------

// Smith's method to take into account both the light direction and the view direction
float gf_smith(vec3 normal, vec3 view, vec3 light, float remapRoughness)
{
	float nDotV = max(dot(normal, view), 0.0f);
	float nDotL = max(dot(normal, light), 0.0f);
	float schlickggx_ndotv = gf_schlickggx(nDotV, remapRoughness);
	float schilckggx_ndotl = gf_schlickggx(nDotL, remapRoughness);

	return schlickggx_ndotv * schilckggx_ndotl;
}

// ------------------------------------------------------------------

// Fresnel approximation
vec3 calculateBaseReflectivity(vec3 surfaceColor, float metalic)
{
	// Surface reflection at zero incidence
	vec3 f0 = vec3(0.04f);
	return mix(f0, surfaceColor, metalic);
}

// ------------------------------------------------------------------

// Schilck's approximation
vec3 fresnel_schilck(float cosTheta, vec3 baseReflectivity)
{
	return baseReflectivity + (1.0f - baseReflectivity) * pow(1.0f - cosTheta, 5.0f);
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------

// Point light attenuation
float calculateAttenuationDistance(vec3 vertexPosW, vec3 lightPosW)
{
	float distance = length(lightPosW - vertexPosW);
	return 1.0f / (distance * distance);
}

// ------------------------------------------------------------------

// Point light attenuation
float calculateAttenuationQuadratic(vec3 vertexPosW, vec3 lightPosW, vec3 attenuation)
{
	float distance = length(lightPosW - vertexPosW);
	return 1.0f / (attenuation.z + attenuation.y * distance + attenuation.x * (distance * distance));
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

// ------------------------------------------------------------------

in VS_OUT
{
	vec2 texCoord;
	vec3 vertexPosW;
	mat3 TBNMatrix;
} fs_in;

PBRMaterial material;

// ------------------------------------------------------------------

out vec4 color;

// ------------------------------------------------------------------

void main()
{
	// Parallax displacement mapping
	vec3 viewDirectionTangent = normalize(fs_in.TBNMatrix * (eyePosW - fs_in.vertexPosW));
	vec2 texCoordParallax = ParallaxMapping(fs_in.texCoord, viewDirectionTangent);
	if (texCoordParallax.x > 1.0f || texCoordParallax.y > 1.0f || texCoordParallax.x < 0.0f || texCoordParallax.y < 0.0f)
	{
		discard;
	}

	// Sample the diffuse texture
	material.albedo = texture(diffuseSampler, texCoordParallax).xyz;
	// Sample the normal texture
	vec3 n = normalize(fs_in.TBNMatrix * (2.0f * texture(normalSampler, texCoordParallax).xyz - 1.0f));
	// Sample the PBR texture
	vec4 pbrMaterial = texture(pbrSampler, texCoordParallax);
	
	// PBR material initialize
	material.roughness = pbrMaterial.x;
	material.metallic = pbrMaterial.y;
	material.ao = pbrMaterial.z;

	// Light color
	vec3 lightColor = vec3(23.47f, 21.31f, 20.79f);
	// View direction
	vec3 v = normalize(eyePosW - fs_in.vertexPosW);
	// Point/directional light direction
	vec3 l = normalize(pointLight[0].lightPosition - fs_in.vertexPosW);
	// Cos theta
	float cosTheta = max(dot(n, l), 0.0f);
	// Calculate attenuation
	float attenuation = calculateAttenuationQuadratic(fs_in.vertexPosW, pointLight[0].lightPosition, pointLight[0].attenuation);
	// Calculate radiance
	vec3 radiance = pointLight[0].diffuseLight * attenuation * cosTheta;
	// Calculate the halfway vector
	vec3 h = normalize(v + l);

	// Calculate f0 - base reflectivity
	vec3 f0 = calculateBaseReflectivity(material.albedo, material.metallic);
	// Calculate Schlick's approximation for the Fresnel factor
	vec3 F = fresnel_schilck(max(dot(h, v), 0.0f), f0);
	// Calculate the geometry function
	float GF = gf_smith(n, v, l, roughnessRemapDielectrics(material.roughness));
	// Calculate the normal distribution function
	float NDF = ndf_ggxtr(n, h, material.roughness);
	// Calculate BRDF Cook-Torrance
	vec3 nom = NDF * GF * F;
	float denom = 4.0f * max(dot(n, v), 0.0f) * cosTheta + 0.001f;
	vec3 brdf = nom / denom;

	// Calculate refracted/reflected incoming light ratio
	vec3 ks = F;
	vec3 kd = vec3(1.0f) - ks;
	// Cancel kd if the material is metallic
	kd *= (1.0f - material.metallic);

	// Calculate irradiance
	vec3 lambert = material.albedo / PI;
	vec3 irradiance = (kd * lambert + brdf) * radiance;

	// Calculate ambient lighting
	vec3 ambient = vec3(0.03f) * material.albedo * material.ao;
	// Calculate fragment final color
	vec3 col = ambient + irradiance;

	// Fragment color
	color = vec4(col, 1.0f);
}

// ------------------------------------------------------------------