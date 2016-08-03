#version 430

in vec2 TexCoord;

out vec4 color;

uniform sampler2D hdrBuffer;
uniform float exposure;
uniform bool hdrEnabled;
uniform float gamma;

void main()
{
	// Sample the hdr buffer
	vec3 hdrColor = texture(hdrBuffer, TexCoord).rgb;
	
	vec3 result;
	if (hdrEnabled == true)
	{
		// Apply the tone mapping algorithm HDR -> LDR
		result = vec3(1.0f) - exp(-hdrColor * exposure);
	}
	else
	{
		// Use the HDR color values and let the fragment shader clamp the values
		result = hdrColor;
	}
	
	// Apply the gamma correction
	result = pow(result, vec3(1.0f / gamma));
	
	color = vec4(result, 1.0f);
}