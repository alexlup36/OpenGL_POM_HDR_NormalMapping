#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec3 vertexTangent;

uniform mat4 wvpMatrix;

void main()
{
	gl_Position = wvpMatrix * vec4(vertexPosition, 1.0f);
}