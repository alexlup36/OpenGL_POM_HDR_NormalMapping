#version 430 core

// Input data
in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;

// Output data
out vec2 TexCoord;

void main()
{
	// Transform the vertex position by the MVP matrix
	gl_Position = vec4(vertexPosition, 1.0f);

	// Pass the UV coordinates
	TexCoord = vertexTexCoord;
}