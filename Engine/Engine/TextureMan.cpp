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

Texture* TextureMan::getTexture(const std::string& texturePath, 
	TextureType textureType)
{
	// Look for the texture
	auto& texture = m_textureMap.find(texturePath);
	if (texture != m_textureMap.end())
	{
		// We found the texture
		return texture->second;
	}
	else
	{
		// Create texture
		Texture* newTexture = new Texture(texturePath, textureType);
		if (newTexture != nullptr)
		{
			// Add texture to cache
			m_textureMap[texturePath] = newTexture;
			return newTexture;
		}
		else
		{
			std::cout << "Failed to create texture: " << texturePath << "\n";
			assert(newTexture);
			return nullptr;
		}
	}
}

// ----------------------------------------------------------------------------s

Texture* TextureMan::getPBRTexture(const std::string& texturePath,
	PBRTextureType textureType)
{
	// Look for the texture
	auto& texture = m_textureMap.find(texturePath);
	if (texture != m_textureMap.end())
	{
		// We found the texture
		return texture->second;
	}
	else
	{
		// Create texture
		Texture* newTexture = new Texture(texturePath, textureType);
		if (newTexture != nullptr)
		{
			// Add texture to cache
			m_textureMap[texturePath] = newTexture;
			return newTexture;
		}
		else
		{
			std::cout << "Failed to create texture: " << texturePath << "\n";
			assert(newTexture);
			return nullptr;
		}
	}
}

// ----------------------------------------------------------------------------