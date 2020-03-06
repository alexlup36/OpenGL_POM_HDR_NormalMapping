#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexTexCoord;
in layout(location = 2) vec3 vertexNormal;
in layout(location = 3) vec3 vertexTangent;

out VS_OUT
{
	vec2 texCoord;
	vec3 vertexPosW;
	mat3 TBNMatrix;
} vs_out;

uniform mat4 wvpMatrix;
uniform mat4 wMatrix;
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
	vs_out.TBNMatrix = mat3(t, b, n);
}

void main()
{
	// Calculate fragment position in screen space
	gl_Position = wvpMatrix * vec4(vertexPosition, 1.0f);
	
	// Calculate vertex position in world coordinates
	vs_out.vertexPosW 	= vec3(wMatrix * vec4(vertexPosition, 1.0f));
	// Pass the texture coordinates
	vs_out.texCoord	= vertexTexCoord;
	// Calculate the TNB matrix for normal mapping
	calculateTNBMatrix();
}