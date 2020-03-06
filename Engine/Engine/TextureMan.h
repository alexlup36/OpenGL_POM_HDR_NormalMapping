#ifndef TEXTUREMAN_H
#define TEXTUREMAN_H

// ----------------------------------------------------------------------------

#include <vector>
#include <map>

#include "Texture.h"

// ----------------------------------------------------------------------------

class TextureMan
{
private:
	TextureMan(void);
	~TextureMan(void);

public:

	// Static access function
	static TextureMan& Instance()
	{
		static TextureMan refInstance;
		return refInstance;
	}

	void addTexture(Texture* texture);
	Texture* getTexture(const std::string& textureName, TextureType textureType);
	Texture* getPBRTexture(const std::string& texturePath, PBRTextureType textureType);

private:
	std::vector<Texture*> m_vTextureList;
	std::map<const std::string, Texture*> m_textureMap;
};

// ----------------------------------------------------------------------------

#endif // TEXTUREMAN_H