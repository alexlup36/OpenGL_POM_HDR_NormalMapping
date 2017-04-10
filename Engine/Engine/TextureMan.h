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
	const Texture* getTexture(const std::string& textureName) const;

private:
	std::vector<Texture*> m_vTextureList;
	std::map<std::string, Texture*> m_textureMap;
};

// ----------------------------------------------------------------------------

#endif // TEXTUREMAN_H