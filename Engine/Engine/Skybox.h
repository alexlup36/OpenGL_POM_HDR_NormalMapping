#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "Common.h"
#include "Object.h"

class Skybox
{
public:
	Skybox();
	virtual ~Skybox();

	inline GLuint GetSkyboxTextureHandle() { return m_uiSkyboxTextureHandle; }
	GLuint LoadCubeMap(const char** fileNames);

	void Update();
	void Draw();

private:
	// Methods
	void LoadShaders();

	// Members
	GLuint m_uiSkyboxTextureHandle;
	GLuint m_uiUniformSkyboxTextureHandle;

	Object* m_pSkyboxCube;
	//Shader* m_pSkyboxShader;
};

#endif // __SKYBOX_H__