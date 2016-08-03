#version 430 core

in vec2 TexCoord;

uniform sampler2D sampler;

// Output data
out vec4 color;

void main()
{
	color = texture2D(sampler, TexCoord);
}