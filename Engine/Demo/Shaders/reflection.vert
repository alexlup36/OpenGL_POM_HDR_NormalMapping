#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;

out vec3 worldVertexPosition;
out vec3 worldNormalDirection;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;
uniform mat4 nMatrix;

void main()
{
	// Calculate fragment position in screen space
	gl_Position = pMatrix * vMatrix * mMatrix * vec4(vertexPosition, 1.0f);
	
	// Calculate vertex position in world coordinates
	worldVertexPosition = vec3(mMatrix * vec4(vertexPosition, 1.0f));

	worldNormalDirection = normalize((nMatrix * vec4(vertexNormal, 0.0f)).xyz);
}