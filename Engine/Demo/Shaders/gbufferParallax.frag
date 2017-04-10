#version 450 core

// ----------------------------------------------------------------------------

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

// ----------------------------------------------------------------------------

in vec3 PositionW;
in vec2 TexCoords;
in mat3 TBNMatrix;

// ----------------------------------------------------------------------------

uniform vec3 eyePosW;
uniform float dispMapScale;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;
uniform sampler2D displacementSampler;

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
	// Parallax displacement mapping
	vec3 viewDirectionTangent = normalize(TBNMatrix * (eyePosW - PositionW));
	vec2 texCoordParallax = ParallaxMapping(TexCoords, viewDirectionTangent);
	if (texCoordParallax.x > 1.0f || texCoordParallax.y > 1.0f || texCoordParallax.x < 0.0f || texCoordParallax.y < 0.0f)
	{
		discard;
	}
	
	// Position in world space
	gPosition = PositionW;
	// Normal in world space
	gNormal = normalize(TBNMatrix * (2.0f * texture(normalSampler, texCoordParallax).xyz - 1.0f));
	// Fill the albedo and specular components
	gAlbedoSpec.rgb = texture(diffuseSampler, texCoordParallax).rgb;
	gAlbedoSpec.a = texture(specularSampler, texCoordParallax).r;
}