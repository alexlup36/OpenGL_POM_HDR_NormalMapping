#version 430

uniform samplerCube skyboxCubeMap;

in vec3 VertexPosition;

out vec4 color;

void main()
{
	color = texture(skyboxCubeMap, VertexPosition);
}