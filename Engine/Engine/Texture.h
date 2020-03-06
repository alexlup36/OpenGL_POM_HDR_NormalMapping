#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Common.h"
#include <string>

enum class TextureType
{
	Diffuse,
	Normal,
	Specular,
	Displacement,
};

enum class PBRTextureType
{
	Albedo,
	PBR,
	Normal,
	Displacement,
};

class Texture
{
public:
	Texture( GLuint textureHandler );
	Texture(const std::string& sFileName, TextureType type, bool bImmutableStorage = true, bool bEnableMipmaps = true);
	Texture(const std::string& sFileName, PBRTextureType type, bool bImmutableStorage = true, bool bEnableMipmaps = true);
	virtual ~Texture();

	static void CreateTexture(int iWidth, int iHeight, bool bDepth, GLuint& uiTextureID);
	void Bind(unsigned int unit, GLuint program);
	GLuint GetHandler();
	inline const std::string& getPath() const { return m_sTexturePath; }

protected:

private:
	Texture( const Texture& other ) {}
	void operator=( const Texture& other ) {}

	GLuint m_uiTexture;
	bool m_bSRGB;
	std::string m_sTexturePath;
};

#endif // __TEXTURE_H__