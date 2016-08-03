#include "Texture.h"

#include <iostream>
#include <cassert>
#include "stb_image.h"
#include <SOIL2.h>

namespace Engine
{
	Texture::Texture(GLuint textureHandler)
	{
		m_uiTexture = textureHandler;
	}

	Texture::Texture(const std::string sFileName, TextureType type, bool bImmutableStorage, bool bEnableMipmaps)
	{
		// --------------------------------------------------------------------------
		// Load texture data from file

		int uiWidth, uiHeight, uiComponents;

		// Get the texture data from the file

		// Using soil
		unsigned char* sImageData = SOIL_load_image( sFileName.c_str(), &uiWidth, &uiHeight, &uiComponents, 4);

		if ( sImageData == NULL )
		{
			std::cout << "Texture loading failed " << sFileName << std::endl;
		}
		else
		{
			std::cout << "Texture data loaded successfully " << sFileName << std::endl;
		}

		// --------------------------------------------------------------------------

		// Create the texture handle
		glGenTextures( 1, &m_uiTexture );
		// Bind the current texture to the texture2D target
		glBindTexture( GL_TEXTURE_2D, m_uiTexture );

		// --------------------------------------------------------------------------

		// Set texture parameters
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// --------------------------------------------------------------------------

		switch (type)
		{
		case TextureType::Diffuse:
			m_bSRGB = true;
			break;
		case TextureType::Normal:
			m_bSRGB = false;
			break;
		case TextureType::Specular:
			m_bSRGB = false;
			break;
		case TextureType::Displacement:
			m_bSRGB = false;
		default:
			break;
		}

		// Allocate memory for the texture
		if (m_bSRGB)
		{
			// Mutable storage - Set texture data - convert colors to linear space so we can apply color correction
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, uiWidth, uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sImageData);
		}
		else
		{
			if (bImmutableStorage)
			{
				// Immutable storage allocation
				glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, uiWidth, uiHeight);
				// Copy texture data
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, uiWidth, uiHeight, GL_RGBA, GL_UNSIGNED_BYTE, sImageData);
			}
			else
			{
				// Mutable storage - Set texture data
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uiWidth, uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sImageData);
			}
		}

		// --------------------------------------------------------------------------

		// Enable mip-maps
		if ( bEnableMipmaps == true )
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		// --------------------------------------------------------------------------

		// Delete texture data
		if (sImageData != nullptr)
		{
			SOIL_free_image_data(sImageData);
			sImageData = nullptr;
		}

		// --------------------------------------------------------------------------
		
		// Unbind the current texture
		glBindTexture( GL_TEXTURE_2D, 0 );
	}


	Texture::~Texture()
	{
		glDeleteTextures( 1, &m_uiTexture );
	}

	// Create empty texture
	void Texture::CreateTexture(int iWidth, 
		int iHeight, 
		bool bDepth,
		GLuint& uiTextureID)
	{
		glGenTextures(1, &uiTextureID);
		glBindTexture(GL_TEXTURE_2D, uiTextureID);
		glTexImage2D(GL_TEXTURE_2D, 
			0, 
			bDepth ? GL_DEPTH_COMPONENT : GL_RGBA, 
			iWidth, 
			iHeight, 
			0, 
			bDepth ? GL_DEPTH_COMPONENT : GL_RGBA,
			GL_UNSIGNED_BYTE, 
			NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Bind(unsigned int unit, GLuint program)
	{
		assert( unit >= 0 && unit <= 32 );

		// Set the texture unit
		glActiveTexture( GLenum(GL_TEXTURE0 + unit) );

		// Bind the texture
		glBindTexture( GL_TEXTURE_2D, m_uiTexture );

		switch (unit)
		{
		case 0:
		{
			// Bind the diffuse sampler
			int location = glGetUniformLocation(program, "diffuseSampler");

			glUniform1i(location, unit);
			break;
		}
		case 1:
		{
			// Bind the normal sampler
			int location = glGetUniformLocation(program, "normalSampler");

			glUniform1i(location, unit);
			break;
		}
		case 2:
		{
			// Bind the displacement map sampler
			int location = glGetUniformLocation(program, "displacementSampler");

			glUniform1i(location, unit);
			break;
		}
		case 3:
		{
			// Bind the specular map sampler
			int location = glGetUniformLocation(program, "specularSampler");

			glUniform1i(location, unit);
			break;
		}
			
		default:
			break;
		}
	}

	GLuint Texture::GetHandler()
	{
		return m_uiTexture;
	}
}