#version 430

uniform sampler2D diffuseSampler;
uniform sampler2D normalSampler;

uniform DirectionalLight
{
    vec4 lightDirection;
    vec4 lightHalfVector;
	vec4 ambientLight;
	vec4 diffuseLight;
	vec4 specularLight;
};

uniform Material
{
	vec4 vMatEmission;
	vec4 vMatAmbient;
	vec4 vMatDiffuse;
	vec4 vMatSpecular;
	float fMatShineness;
};

in vec2 TexCoord;
in vec3 VertexNormal;
in vec3 VertexToEye;
in vec3 LightPos;
in vec3 VertexWorld;

out vec4 color;

void main()
{
	vec3 nNV, nHV, nLV, nEV;
	float NdotL, NdotHV;

	color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Sample the diffuse and normal textures
	vec4 textureDiffuse = texture(diffuseSampler, TexCoord);
	vec4 textureNormal = texture(normalSampler, TexCoord);

	vec4 ambient = ambientLight * vMatAmbient;
	vec4 diffuse = diffuseLight * vMatDiffuse * textureDiffuse;
	vec4 specular;
	
	// Normalize
	nLV = normalize(LightPos);
	nNV = normalize(VertexNormal);
	nEV = normalize(VertexToEye);
	nHV = normalize(nLV + nEV);
	
	NdotL = dot(nLV, nNV);
	diffuse = max(NdotL, 0.0f) * diffuse;

	// Blin-Phong - Half vector
	NdotHV = dot(nNV, nHV);

	if (NdotL < 0.0f)
	{
		specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		specular = specularLight * vMatSpecular * pow(max(NdotHV, 0.0f), fMatShineness);
	}

	specular = clamp(specular, 0.0f, 1.0f);

	//color = textureNormal;//textureNormal;//vec4((ambient + diffuse + specular).xyz, 1.0f); vec4(TexCoord, 0.0f, 1.0f);//
	color = mix(textureNormal, textureDiffuse, 0.5f);
}