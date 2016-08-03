#version 430 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 vertexUV;

out vec2 UV;

void main()
{
	vec2 vertexPositionHomogeneousSpace = (vertexPosition - vec2(400, 300)) / vec2(400, 300);
	
	gl_Position = vec4(vertexPositionHomogeneousSpace, 0, 1);
	UV = vertexUV;
}
