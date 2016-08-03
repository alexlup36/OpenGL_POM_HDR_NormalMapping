#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec3 vertexTangent;

out vec2 texCoord;
out vec3 vertexW;
out vec3 normalW;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;
uniform mat4 nMatrix;

void main()
{
	// Calculate fragment position in screen space
	gl_Position = pMatrix * vMatrix * mMatrix * vec4(vertexPosition, 1.0f);
	
	// Calculate vertex position in world coordinates
	vertexW 	= vec3(mMatrix * vec4(vertexPosition, 1.0f));
	// Calculate normal direction in world coordinates
	normalW 	= normalize((nMatrix * vec4(vertexNormal, 0.0f)).xyz);
	
	// Pass the texture coordinates
	texCoord	= vertexTexCoord;	
}