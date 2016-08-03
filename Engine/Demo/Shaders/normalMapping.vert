#version 450

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec3 vertexTangent;

out vec2 texCoord;
out vec3 vertexW;
out mat3 TBNMatrix;
out vec3 normalW;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;
uniform mat4 nMatrix;

void calculateTNBMatrix()
{
	// Transform the normal, tangent and calculate binormals
	vec3 n = normalize(mat3(nMatrix) * vertexNormal);
	vec3 t = normalize(mat3(nMatrix) * vertexTangent);
	
	// Make sure the t and n vectors are orthogonal
	t = normalize(t - dot(t, n) * n);
	
	vec3 b = normalize(cross(t, n)); // Order important
	
	// Create the TBN matrix
	TBNMatrix = mat3(t, b, n);
}

void main()
{
	// Calculate fragment position in screen space
	gl_Position = pMatrix * vMatrix * mMatrix * vec4(vertexPosition, 1.0f);
	
	// Calculate vertex position in world coordinates
	vertexW 	= vec3(mMatrix * vec4(vertexPosition, 1.0f));
	normalW 	= normalize(mat3(nMatrix) * vertexNormal);
	
	// Pass the texture coordinates
	texCoord	= vertexTexCoord;
	
	// Calculate the TNB matrix for normal mapping
	calculateTNBMatrix();
}