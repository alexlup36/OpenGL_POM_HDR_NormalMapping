#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec3 vertexTangent;

out vec2 TexCoord;
out vec3 VertexNormal;
out vec3 VertexToEye;
out vec3 LightPos;
out vec3 VertexWorld;

uniform mat4 mvMatrix;
uniform mat4 pMatrix;
uniform vec3 eyePosW;
uniform vec4 lightPositionW;
uniform mat4 normalMatrix;

void main()
{
	vec4 vertexWorld = mvMatrix * vec4(vertexPosition, 1.0f);
	gl_Position		 = pMatrix * vertexWorld;
	VertexWorld		 = vertexWorld.xyz;
	
	// Point light
	LightPos		 = lightPositionW.xyz - vertexPosition.xyz;
	
	if (lightPositionW.w == 0.0f)
	{
		// Directional light
		LightPos = lightPositionW.xyz;
	}

	VertexToEye		= eyePosW - vertexPosition.xyz;

	VertexNormal 	= normalize((normalMatrix * vec4(vertexNormal, 0.0f)).xyz);

	TexCoord		= vertexTexCoord;
}