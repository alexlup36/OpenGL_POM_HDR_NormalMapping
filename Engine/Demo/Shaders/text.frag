#version 430 core

in vec2 UV;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D diffuseSampler;

void main()
{
	color = texture2D(diffuseSampler, UV);
}