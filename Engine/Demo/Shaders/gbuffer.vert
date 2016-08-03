#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec3 PositionW;
out vec2 TexCoords;
out mat3 TBNMatrix;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;
uniform mat4 nMatrix;

void calculateTNBMatrix(vec3 normal, vec3 tangent)
{
	// Transform the normal, tangent and calculate binormals
	vec3 n = normalize(mat3(nMatrix) * normal);
	vec3 t = normalize(mat3(nMatrix) * tangent);
	
	// Make sure the t and n vectors are orthogonal
	t = normalize(t - dot(t, n) * n);
	
	vec3 b = normalize(cross(t, n)); // Order important
	
	// Create the TBN matrix
	TBNMatrix = mat3(t, b, n);
}

void main()
{
	vec4 positionWorld = mMatrix * vec4(position, 1.0f);
	
	// Pass the world position to the fragment shader
	PositionW = positionWorld.xyz;
	
	// Calculate the screen position
	gl_Position = pMatrix * vMatrix * positionWorld;

	TexCoords = texCoords;
	
	calculateTNBMatrix(normal, tangent);
}