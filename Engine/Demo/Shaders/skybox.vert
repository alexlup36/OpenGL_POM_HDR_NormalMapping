#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;

out vec3 VertexPosition;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

void main()
{
	// Calculate fragment position in screen space
	gl_Position = pMatrix * vMatrix * mMatrix * vec4(vertexPosition, 1.0f);
	
	// Calculate vertex position in world coordinates
	VertexPosition 	= vec3(mMatrix * vec4(vertexPosition, 1.0f));
}