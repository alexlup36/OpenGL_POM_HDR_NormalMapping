#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec3 vertexTangent;

out VS_OUT
{
	vec2 texCoord;
	vec3 vertexNormal;
	vec3 vertexPosW;
} vs_out;

uniform mat4 wvpMatrix;
uniform mat4 wMatrix;
uniform mat4 nMatrix;

void main()
{
	// Calculate fragment position in screen space
	gl_Position = wvpMatrix * vec4(vertexPosition, 1.0f);
	
	// Calculate vertex position in world coordinates
	vs_out.vertexPosW 	= vec3(wMatrix * vec4(vertexPosition, 1.0f));
	// Calculate normal direction in world coordinates
	vs_out.vertexNormal 	= (nMatrix * vec4(vertexNormal, 0.0f)).xyz;
	// Pass the texture coordinates
	vs_out.texCoord	= vertexTexCoord;
}