#version 430

uniform samplerCube cubeMap;
uniform vec3 eyePosW;

in vec3 worldVertexPosition;
in vec3 worldNormalDirection;

out vec4 color;

void main()
{
	vec3 viewDirection = normalize(eyePosW - worldVertexPosition);
	vec3 normal = normalize(worldNormalDirection);

	vec3 reflection = reflect(-viewDirection, normal);

	color = texture(cubeMap, reflection);
}