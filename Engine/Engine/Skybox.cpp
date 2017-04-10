#include "Skybox.h"

#include <SOIL2.h>

#include "ObjectMan.h"
//#include "ShaderMan.h"
#include "CameraMan.h"
#include "stb_image.h"


Skybox::Skybox()
{
	// Load the shaders
	LoadShaders();

	// Add cube
	m_pSkyboxCube = new Engine::Object("Skybox",
		".\\Assets\\cube1.obj",
		m_pSkyboxShader,
		new Engine::Texture(".\\Assets\\bricks.jpg", TextureType::Diffuse, true, false));
}


Skybox::~Skybox()
{
	if (m_pSkyboxCube != NULL)
	{
		delete m_pSkyboxCube;
		m_pSkyboxCube = NULL;
	}
}

void
Skybox::LoadShaders()
{
	GLClearErrors();

	// Initialize shaders
	m_pSkyboxShader = new Engine::Shader(".\\Shaders\\skybox.vert", ".\\Shaders\\skybox.frag");

	GLErrorCheck("TestGLApp::LoadShaders");
}

GLuint 
Skybox::LoadCubeMap(const char** fileNames)
{
	// Right, left, bottom, top, front, back
	glGenTextures(1, &m_uiSkyboxTextureHandle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiSkyboxTextureHandle);

	for (int i = 0; i < 6; i++)
	{
		int uiWidth, uiHeight, uiComponents;

		// Get the texture data from the file

		// Using soil
		unsigned char* sImageData = SOIL_load_image(fileNames[i], &uiWidth, &uiHeight, &uiComponents, 4);

		if (sImageData == NULL)
		{
			std::cout << "Texture loading failed " << fileNames[i] << std::endl;
		}
		else
		{
			std::cout << "Texture data loaded successfully " << fileNames[i] << std::endl;
		}

		// Set texture data
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, uiWidth, uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sImageData);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return m_uiSkyboxTextureHandle;
}

void 
Skybox::Update()
{
	glm::vec3 vCameraPosition = CameraMan::Instance().GetActiveCamera()->GetCameraPosition();

	m_pSkyboxCube->Translate(vCameraPosition.x, vCameraPosition.y, vCameraPosition.z);
}

void 
Skybox::Draw()
{
	assert(m_pSkyboxShader != NULL);

	// Disable the depth test
	glDisable(GL_DEPTH_TEST);

	// Enable the shader
	m_pSkyboxShader->Enable();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiSkyboxTextureHandle);

	m_uiUniformSkyboxTextureHandle = glGetUniformLocation(m_pSkyboxShader->ProgramID(), "skyboxCubeMap");
	glUniform1i(m_uiUniformSkyboxTextureHandle, 0);

	// Render
	m_pSkyboxCube->GetShader()->SetTransform(m_pSkyboxCube->GetTransform());
	m_pSkyboxCube->GetShader()->Update();

	m_pSkyboxCube->Render();

	// Disable the shader
	m_pSkyboxShader->Disable();

	// Enable the depth test
	glEnable(GL_DEPTH_TEST);
}