#version 450 core

// ----------------------------------------------------------------------------

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;
layout (location = 3) out vec4 gAlbedoSpec2;
layout (location = 4) out vec3 gNormal2;

// ----------------------------------------------------------------------------

in vec3 PositionW;
in vec2 TexCoords;
in mat3 TBNMatrix;

// ----------------------------------------------------------------------------

uniform vec3 eyePosW;
uniform float dispMapScale;

uniform sampler2D diffuseSampler;
uniform sampler2D diffuseSampler2;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;
uniform sampler2D normalSampler2;
uniform sampler2D displacementSampler;

// ----------------------------------------------------------------------------

void main()
{
	// Position in world space
	gPosition = PositionW;
	// Normal in world space
	gNormal = normalize(TBNMatrix * (2.0f * texture(normalSampler, TexCoords).xyz - 1.0f));
	gNormal2 = normalize(TBNMatrix * (2.0f * texture(normalSampler2, TexCoords).xyz - 1.0f));
	// Fill the albedo and specular components
	gAlbedoSpec.rgb = texture(diffuseSampler, TexCoords).rgb;
	gAlbedoSpec.a = texture(specularSampler, TexCoords).r;
	// Fill the albedo and specular components 2
	gAlbedoSpec2.rgb = texture(diffuseSampler2, TexCoords).rgb;
	gAlbedoSpec2.a = texture(specularSampler, TexCoords).r;
}