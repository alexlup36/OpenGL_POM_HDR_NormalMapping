#include "TextureMan.h"

// ----------------------------------------------------------------------------

TextureMan::TextureMan()
{
}

// ----------------------------------------------------------------------------

TextureMan::~TextureMan()
{
	for each (Texture* currentTexture in m_vTextureList)
	{
		if (currentTexture != nullptr)
		{
			delete currentTexture;
			currentTexture = nullptr;
		}
	}
}

// ----------------------------------------------------------------------------

void TextureMan::addTexture(Texture* texture)
{
	// If the texture doesn't exist in the map, add it
	const std::string& texturePath = texture->getPath();
	if (m_textureMap.find(texturePath) == m_textureMap.end())
	{
		m_textureMap[texturePath] = texture;
		m_vTextureList.push_back(texture);
	}
}

// ----------------------------------------------------------------------------

const Texture* TextureMan::getTexture(const std::string& texturePath) const
{
	// Look for the texture
	auto& texture = m_textureMap.find(texturePath);
	if (texture != m_textureMap.end())
	{
		// We found the texture
		return texture->second;
	}

	return nullptr;
}

// ----------------------------------------------------------------------------