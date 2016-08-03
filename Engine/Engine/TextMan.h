#ifndef __TEXTMAN_H__
#define __TEXTMAN_H__

#include "Shader.h"
#include "Texture.h"
#include "GameComponent.h"

class TextMan : public GameComponent
{
private:
	TextMan(void);
	~TextMan(void);

public:
	
	// Static access function
	static TextMan& Instance()
	{
		static TextMan refInstance;

		return refInstance;
	}

	void Initialize(const char* sFontTexturePath);
	void PrintText(const char* sText, int x, int y, int size);

private:
	Engine::Shader* m_pTextShader;
	Engine::Texture* m_pTextTexture;

	GLuint m_Text2DVertexBufferID;
	GLuint m_Text2DUVBufferID;

	GLuint m_VertexArrayObject;
};

#endif __TEXTMAN_H__