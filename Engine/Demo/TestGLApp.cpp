#include "TestGLApp.h"

// Rendering engine include
#include "Common.h"
#include "GfxStats.h"
#include "ObjectMan.h"
#include "TechniqueMan.h"
#include "UIManager.h"
#include "MappedProperties.h"

TestGLApp::TestGLApp(void)
{
	/*m_pBlinnPhongShader			= nullptrptr;
	m_pReflectionShader				= nullptrptr;
	m_pNormalShader					= nullptrptr;
	m_pParallaxShader				= nullptrptr;
	m_pQuadShader					= nullptrptr;
	m_pHDRShader					= nullptrptr;
	m_pGBufferShaderNormal			= nullptrptr;
	m_pGBufferShaderParallax		= nullptrptr;
	m_pLightingPassShader			= nullptrptr;

	pDirectionalLightTechnique		= nullptrptr;
	pReflectionTechnique			= nullptrptr;
	pNormalMappingTechnique			= nullptrptr;
	pParallaxMappingTechnique		= nullptrptr;
	pBlinnPhongSolidTechnique		= nullptrptr;
	m_pSkybox						= nullptrptr;
	pHDRLightTechnique				= nullptrptr;
	m_pGBufferShaderNormal			= nullptrptr;
	m_pGBufferShaderParallax		= nullptrptr;

	/*m_pHDRRenderToTexture			= nullptrptr;
	m_pShadowMappingRenderToTexture = nullptrptr;*/
}


TestGLApp::~TestGLApp(void)
{
	/*if (pDirectionalLightTechnique != nullptrptr)
	{
		delete pDirectionalLightTechnique;
		pDirectionalLightTechnique = nullptrptr;
	}

	if (pReflectionTechnique != nullptrptr)
	{
		delete pReflectionTechnique;
		pReflectionTechnique = nullptrptr;
	}

	if (pNormalMappingTechnique != nullptrptr)
	{
		delete pNormalMappingTechnique;
		pNormalMappingTechnique = nullptrptr;
	}

	if (pParallaxMappingTechnique != nullptrptr)
	{
		delete pParallaxMappingTechnique;
		pParallaxMappingTechnique = nullptrptr;
	}

	if (pBlinnPhongSolidTechnique != nullptrptr)
	{
		delete pBlinnPhongSolidTechnique;
		pBlinnPhongSolidTechnique = nullptrptr;
	}

	if (pHDRLightTechnique != nullptrptr)
	{
		delete pHDRLightTechnique;
		pHDRLightTechnique = nullptrptr;
	}

	if (m_pGBufferShaderNormal != nullptrptr)
	{
		delete m_pGBufferShaderNormal;
		m_pGBufferShaderNormal = nullptrptr;
	}

	if (m_pGBufferShaderParallax != nullptrptr)
	{
		delete m_pGBufferShaderParallax;
		m_pGBufferShaderParallax = nullptrptr;
	}
	
	if (m_pSkybox != nullptr)
	{
		delete m_pSkybox;
		m_pSkybox = nullptr;
	}

	if (m_pHDRRenderToTexture != nullptrptr)
	{
		delete m_pHDRRenderToTexture;
		m_pHDRRenderToTexture = nullptrptr;
	}

	if (m_pShadowMappingRenderToTexture != nullptrptr)
	{
		delete m_pShadowMappingRenderToTexture;
		m_pShadowMappingRenderToTexture = nullptrptr;
	}*/
}

// Overrides
int 
TestGLApp::Initialize()
{
	GLClearErrors();

	MappedProperties::GetInstance().initialize(".\\data\\test.txt");

	BaseGLApp::Initialize();
	BaseGLApp::SetWindowProperties("OpenGL rendering framework");

	SetupScene();
	GfxStats::Instance().initialize();
	GfxStats::Instance().addStat("objectRender");
	GfxStats::Instance().addStat("frameTime");
	GfxStats::Instance().addStat("textRender");
	GfxStats::Instance().addStat("updateStats");
	GfxStats::Instance().addStat("updateTechnique");

	//UIManager::Instance().init(Core::Window);

	GLErrorCheck("TestGLApp::Initialize");

	// Success
	return 1;
}

void 
TestGLApp::SetupScene()
{
	GLClearErrors();

	// Load shaders -----------------------------------------------------

	LoadShaders();

	// Setup scene ------------------------------------------------------

	// Create a texture to render to
	//Engine::Texture::CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT, false, uiRenderTexture);
	//Engine::Texture::CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT, true, uiDepthTexture);

	//// Generate a framebuffer
	//glGenFramebuffers(1, &uiFBO);
	//glBindFramebuffer(GL_FRAMEBUFFER, uiFBO);

	//// Attach a color buffer
	//glFramebufferTexture2D(GL_FRAMEBUFFER,
	//	GL_COLOR_ATTACHMENT0,
	//	GL_TEXTURE_2D,
	//	uiRenderTexture,
	//	0);

	//// Attach a depth buffer
	//glFramebufferTexture2D(GL_FRAMEBUFFER,
	//	GL_DEPTH_ATTACHMENT,
	//	GL_TEXTURE_2D,
	//	uiDepthTexture,
	//	0);

	//int i = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	//if (i != GL_FRAMEBUFFER_COMPLETE)
	//{
	//	std::cout << "Framebuffer error." << std::endl;
	//}

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ------------------------------------------------------------------
	// Create object
	// Add mesh to the mesh manager

	// Add plane
	/*ObjectMan::GetInstance().AddObject(
		new Engine::Object("Quad",
		".\\Assets\\quad.obj",
		m_pQuadShader,
		new Engine::Texture(uiRenderTexture)));*/

		// Add spheres
		//const unsigned SPHERE_COUNT = 4;

		//for (unsigned i = 1; i <= SPHERE_COUNT; i++)
		//{
		//	// Create object
		//	Engine::Object* tempObject = new Engine::Object("SphereObject",
		//		".\\Assets\\sphere.obj",
		//		m_pNormalShader,
		//		new Engine::Texture(".\\Assets\\bricks.jpg", TextureType::Diffuse, true, false),
		//		new Engine::Texture(".\\Assets\\bricks_normal.jpg", TextureType::Normal, true, false),
		//		new Engine::Texture(".\\Assets\\bricks_disp_inv.png", TextureType::Displacement, true, false));

		//	// Translate object
		//	tempObject->Translate(i * 250.0f, 100.0f, 0.0f);
		//	tempObject->Scale(100.0f / i, 1.0f / i, 100.0f / i);

		//	// Add object to ObjectMan
		//	ObjectMan::GetInstance().AddObject(tempObject);
		//}

		/*Engine::Object* pCamaroObject = new Engine::Object("camaro",
			".\\Assets\\CAMARO.obj",
			m_pBlinnPhongShader);

		ObjectMan::GetInstance().AddObject(pCamaroObject);*/

		// ------------------------------------------------------------------

	GLClearErrors();

	// Create phong technique
	m_pPhongTechnique = new PhongLightTechnique();
	if (m_pPhongTechnique->init() == false)
	{
		std::cout << "Failed to init PhongTechnique. \n";
		return;
	}
	else
	{
		// Add technique to the tech manager
		TechniqueMan::Instance().registerTechnique(m_pPhongTechnique);
	}

	// Create pbr technique
	m_pPBRTechnique = new PBRLightTechnique();
	if (m_pPBRTechnique->init() == false)
	{
		std::cout << "Failed to init PBRTechnique. \n";
		return;
	}
	else
	{
		// Add technique to the tech manager
		TechniqueMan::Instance().registerTechnique(m_pPBRTechnique);
	}

	// Material definition
	Material chromeMaterial;
	chromeMaterial.Ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	chromeMaterial.Diffuse = glm::vec3(0.8f, 0.0f, 0.2f);
	chromeMaterial.Emission = glm::vec3(0.1f, 0.7f, 0.9f);
	chromeMaterial.Specular = glm::vec3(1.0f, 1.0f, 1.0f);
	chromeMaterial.Shineness = 32.0f;

	// PBR material definition
	m_pbrMaterial.albedo = glm::vec3(0.0f, 0.0f, 1.0f);
	m_pbrMaterial.ao = 0.0f;
	m_pbrMaterial.metallic = 0.0f;
	m_pbrMaterial.roughness = 0.0f;

	// Create object
	/*Object* quadPhong0 = new Object("quadPhongTexture",
		".\\Assets\\quad.obj",
		m_pPhongTechnique,
		new Texture(".\\Assets\\snow2_diffuse.jpg", TextureType::Diffuse, true, false),
		new Texture(".\\Assets\\rock1_diffuse.jpg", TextureType::Diffuse, true, false),
		new Texture(".\\Assets\\snow2_normal.jpg", TextureType::Normal, true, false),
		new Texture(".\\Assets\\rock1_normal.jpg", TextureType::Normal, true, false),
		new Texture(".\\Assets\\brick_displacement.jpg", TextureType::Displacement, true, false),
		new Texture(".\\Assets\\brick_specular.jpg", TextureType::Specular, true, false));*/



	GL::Object* quad = new GL::Object("quadObj",
		".\\Assets\\quad.obj",
		m_pPhongTechnique,
		&chromeMaterial);
	quad->Scale(50.0f, 1.0f, 10.0f);
	quad->Translate(0.0f, 0.0f, 0.0f);

	GL::Object* rock = new GL::Object("rock",
		".\\Assets\\rock.obj",
		m_pPhongTechnique,
		&chromeMaterial);
	rock->Scale(3.0f, 3.0f, 3.0f);
	rock->Translate(10.0f, 2.0f, 0.0f);

	GL::Object* cyborg = new GL::Object("cyborg",
		".\\Assets\\cyborg.obj",
		m_pPBRTechnique,
		&m_pbrMaterial);
	cyborg->Scale(5.0f, 5.0f, 5.0f);
	cyborg->Translate(20.0f, 0.0f, 0.0f);

	GL::Object* nanosuit = new GL::Object("nanosuit",
		".\\Assets\\nanosuit.obj",
		m_pPhongTechnique,
		&chromeMaterial);
	nanosuit->Translate(30.0f, 0.0f, 0.0f);

	GL::Object* planet = new GL::Object("planet",
		".\\Assets\\planet.obj",
		m_pPhongTechnique,
		&chromeMaterial);
	//planet->Scale(10.0f, 10.0f, 10.0f);
	planet->Translate(40.0f, 2.0f, 0.0f);

	// Add object to object manager
	ObjectMan::GetInstance().addObject(quad);
	ObjectMan::GetInstance().addObject(rock);
	ObjectMan::GetInstance().addObject(cyborg);
	ObjectMan::GetInstance().addObject(nanosuit);
	ObjectMan::GetInstance().addObject(planet);

	// --------------------------------------------------------
	// Test PBR
	unsigned int metallicCount = 10;
	unsigned int roughnessCount = 10;
	float xOffset = 50.0f;
	float zOffset = 50.0f;

	m_pbrMaterial.albedo = glm::vec3(0.0f, 0.0f, 1.0f);
	m_pbrMaterial.ao = 0.0f;
	m_pbrMaterial.metallic = 0.0f;
	m_pbrMaterial.roughness = 0.0f;

	for (unsigned int metallicIndex = 0; metallicIndex <= metallicCount; ++metallicIndex)
	{
		for (unsigned int roughnessIndex = 0; roughnessIndex <= roughnessCount; ++roughnessIndex)
		{
			// Create object
			GL::Object* planet = new GL::Object("planet" + std::to_string(metallicIndex * roughnessCount + roughnessIndex),
				".\\Assets\\planet.obj",
				m_pPBRTechnique,
				&m_pbrMaterial);
			planet->Translate(10.0f * metallicIndex, 2.0f, 10.0f * roughnessIndex);

			// Add object to scene
			ObjectMan::GetInstance().addObject(planet);

			m_pbrMaterial.roughness += (1.0f / roughnessCount);
		}

		m_pbrMaterial.metallic += (1.0f / metallicCount);
	}

	// ------------------------------------------------------------------

	//Engine::Object* groundObjectParallax = new Engine::Object("groundParallax",
	//	".\\Assets\\quad.obj",
	//	m_pNormalShader,
	//	new Engine::Texture(".\\Assets\\rock1_diffuse.jpg", TextureType::Diffuse, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\rock1_normal.jpg", TextureType::Normal, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\brick_displacement.jpg", TextureType::Displacement, true, false),
	//	new Engine::Texture(".\\Assets\\brick_specular.jpg", TextureType::Specular, true, false));
	//groundObjectParallax->Scale(100.0f, 1.0f, 100.0f);
	//groundObjectParallax->Translate(-250.0f, -100.0f, 0);

	//ObjectMan::GetInstance().AddObject(groundObjectParallax);

	//// ------------------------------------------------------------------

	//Engine::Object* groundObject2 = new Engine::Object("ground2",
	//	".\\Assets\\quad.obj",
	//	m_pNormalShader,
	//	new Engine::Texture(".\\Assets\\bricks.jpg", TextureType::Diffuse, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\bricks_normal.jpg", TextureType::Normal, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\bricks_disp_inv.png", TextureType::Displacement, true, false));
	//groundObject2->Scale(100.0f, 1.0f, 100.0f);
	//groundObject2->Translate(0.0f, 0.0f, 250.0f);

	//ObjectMan::GetInstance().AddObject(groundObject2);

	//// ------------------------------------------------------------------

	//Engine::Object* groundObject3 = new Engine::Object("ground3",
	//	".\\Assets\\quad.obj",
	//	m_pNormalShader,
	//	new Engine::Texture(".\\Assets\\bricks2.jpg", TextureType::Diffuse, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\bricks2_normal.jpg", TextureType::Normal, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\bricks2_disp_inv.jpg", TextureType::Displacement, true, false));
	//groundObject3->Scale(100.0f, 1.0f, 100.0f);
	//groundObject3->Translate(250.0f, 0.0f, 0.0f);

	//ObjectMan::GetInstance().AddObject(groundObject3);

	//// ------------------------------------------------------------------

	//Engine::Object* groundObject4 = new Engine::Object("ground4",
	//	".\\Assets\\quad.obj",
	//	m_pBlinnPhongShader,
	//	new Engine::Texture(".\\Assets\\bricks2.jpg", TextureType::Diffuse, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\bricks2_normal.jpg", TextureType::Normal, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\bricks2_disp_inv.jpg", TextureType::Displacement, true, false),
	//	new Engine::Texture(".\\Assets\\bricks2_disp_inv.jpg", TextureType::Specular, true, false));
	//groundObject4->Scale(100.0f, 1.0f, 100.0f);
	//groundObject4->Translate(250.0f, -100.0f, 250.0f);

	//ObjectMan::GetInstance().AddObject(groundObject4);

	//// ------------------------------------------------------------------

	//Engine::Object* groundObject5 = new Engine::Object("ground5",
	//	".\\Assets\\quad.obj",
	//	m_pNormalShader,
	//	new Engine::Texture(".\\Assets\\wood.png", TextureType::Diffuse, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\wood_normal.png", TextureType::Normal, true, false),
	//	nullptrptr,
	//	new Engine::Texture(".\\Assets\\wood_disp_inv.png", TextureType::Displacement, true, false));
	//groundObject5->Scale(100.0f, 1.0f, 100.0f);
	//groundObject5->Translate(500.0f, 0.0f, 0.0f);

	//ObjectMan::GetInstance().AddObject(groundObject5);

	// ------------------------------------------------------------------

	// Skybox
	/*const char* szSkyboxFiles[] = { ".\\Assets\\skybox\\right.bmp",
		".\\Assets\\skybox\\left.bmp",
		".\\Assets\\skybox\\top.bmp",
		".\\Assets\\skybox\\bottom.bmp",
		".\\Assets\\skybox\\front.bmp",
		".\\Assets\\skybox\\back.bmp" };
	m_pSkybox = new Skybox();
	m_pSkybox->LoadCubeMap(&szSkyboxFiles[0]);*/

	GLErrorCheck("Create object error.!!!!!!!!!!!!!!!!!");

	// ------------------------------------------------------------------

	// Create camera
	/*CameraMan::Instance().CreateCamera("Cam1", (float)M_PI_4, 0.1f, 3000.0f);
	CameraMan::Instance().GetCamera("Cam1")->SetPosition(glm::vec3(61.4116f, 303.988f, -251.391f));
	CameraMan::Instance().GetCamera("Cam1")->SetTarget(glm::vec3(61.6961f, 303.262f, -250.765f));
	CameraMan::Instance().GetCamera("Cam1")->SetUp(glm::vec3(0.300814f, 0.687144f, 0.66132f));*/

	GLClearErrors();

	CameraMan::Instance().CreateCamera("Cam1", 45.0f, 1.0f, 3000.0f);
	//CameraMan::Instance().GetCamera("Cam1")->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	//CameraMan::Instance().GetCamera("Cam1")->SetDirection(glm::vec3(0.0f, 0.0f, 0.0f));

	GLErrorCheck("Camera setup error.!!!!!!!!!!!!!!!!!");

	// ------------------------------------------------------------------

	GLClearErrors();

	// Lighting
	// Directional light definition
	DirectionalLight dirLightStruct;
	dirLightStruct.AmbientLight			= glm::vec3(1.3f, 1.3f, 1.3f);
	dirLightStruct.DiffuseLight			= glm::vec3(0.5f, 0.5f, 0.5f);
	dirLightStruct.Position				= glm::vec3(-0.2f, -1.0f, -0.3f);
	dirLightStruct.SpecularLight		= glm::vec3(1.0f, 1.0f, 1.0f);

	// Point light definition
	m_pointLightStruct1.AmbientLight		= glm::vec3(10.0f, 10.0f, 10.0f);
	m_pointLightStruct1.DiffuseLight		= glm::vec3(100.0f, 100.0f, 100.0f);
	m_pointLightStruct1.Position			= glm::vec3(25.0f, 25.0f, 25.0f);
	m_pointLightStruct1.SpecularLight		= glm::vec3(100.0f, 100.0f, 100.0f);
	m_pointLightStruct1.Attenuation		= glm::vec3(0.0028f, 0.027f, 1.0f);

	m_pointLightStruct2.AmbientLight		= glm::vec3(10.0f, 5.0f, 10.0f);
	m_pointLightStruct2.DiffuseLight		= glm::vec3(100.0f, 50.0f, 200.0f);
	m_pointLightStruct2.Position			= glm::vec3(300.0f, 5.0f, 250.0f);
	m_pointLightStruct2.SpecularLight		= glm::vec3(1.0f, 1.0f, 1.0f);
	m_pointLightStruct2.Attenuation		= glm::vec3(0.0028f, 0.027f, 1.0f);
	
	GLErrorCheck("Light setup error.!!!!!!!!!!!!!!!!!");

	// Simple shader

	GLClearErrors();

	// Create light techniques
	/*pDirectionalLightTechnique = new LightTechnique(m_pBlinnPhongShader);
	pDirectionalLightTechnique->SetDirectionalLight(dirLightStruct);
	pDirectionalLightTechnique->SetMaterial(materialStruct);*/

	/*pDirectionalLightTechnique = new LightTechnique(m_pLightingPassShader);
	pDirectionalLightTechnique->SetDirectionalLight(dirLightStruct);
	pDirectionalLightTechnique->SetMaterial(planeMaterialChromeStruct);

	pGBufferTechniqueNormal = new LightTechnique(m_pGBufferShaderNormal);
	pGBufferTechniqueParallax = new LightTechnique(m_pGBufferShaderParallax);
	pGBufferTechniqueParallax->SetDisplacementMapProperties(0.03f);*/

	// Reflection shader
	//pReflectionTechnique = new LightTechnique(m_pReflectionShader);
	//pReflectionTechnique->SetCubeMap(m_pSkybox->GetSkyboxTextureHandle());

	// Normal mapping shader
	//pNormalMappingTechnique = new LightTechnique(m_pNormalShader);
	//pNormalMappingTechnique->SetDirectionalLight(dirLightStruct);
	//pNormalMappingTechnique->AddPointLight(pointLightStruct1);
	//pNormalMappingTechnique->AddPointLight(pointLightStruct2);
	//pNormalMappingTechnique->SetMaterial(planeMaterialChromeStruct);
	//pNormalMappingTechnique->SetGamma(2.2f);
	//pNormalMappingTechnique->SetDisplacementMapProperties(0.05f);

	//// Parallax mapping shader
	//pParallaxMappingTechnique = new LightTechnique(m_pParallaxShader);
	//pParallaxMappingTechnique->SetDirectionalLight(dirLightStruct);
	//pParallaxMappingTechnique->AddPointLight(pointLightStruct1);
	//pParallaxMappingTechnique->AddPointLight(pointLightStruct2);
	//pParallaxMappingTechnique->SetMaterial(planeMaterialChromeStruct);
	//pParallaxMappingTechnique->SetGamma(2.2f);
	//pParallaxMappingTechnique->SetDisplacementMapProperties(0.05f);

	// Blinn-Phong solid shader
	glGetError();
	//m_pPhongTechnique->addDirectionalLight(dirLightStruct);
	//GLErrorCheck("PhongTechnique setup error");
	m_pPhongTechnique->addPointLight(m_pointLightStruct2);
	//GLErrorCheck("Technique setup error.!!!!!!!!!!!!!!!!!");
	//m_pPhongTechnique->addPointLight(pointLightStruct2);

	// PBR shader
	m_pPBRTechnique->addPointLight(m_pointLightStruct1);

	GLErrorCheck("Technique setup error.!!!!!!!!!!!!!!!!!");

	// ------------------------------------------------------------------

	GLClearErrors();

	/*m_pHDRRenderToTexture = new RenderToTexture();
	m_pHDRRenderToTexture->SetupFramebuffer(GL_RGB16F, GL_FLOAT, true, false);
	m_pHDRRenderToTexture->SetupQuadGeometry();

	pHDRLightTechnique = new HDRLightingTechnique(m_pHDRShader);
	pHDRLightTechnique->SetExposure(0.2f);
	pHDRLightTechnique->SetHDREnabled(GL_TRUE);
	pHDRLightTechnique->SetGamma(2.2f);*/

	GLErrorCheck("Technique setup2 error.!!!!!!!!!!!!!!!!!");
	// ------------------------------------------------------------------

	//m_pShadowMappingRenderToTexture = new RenderToTexture();
	//m_pShadowMappingRenderToTexture->SetupFramebuffer(GL_RGB16F, GL_FLOAT, false, true);
	//m_pShadowMappingRenderToTexture->SetupQuadGeometry();

	

	// ------------------------------------------------------------------
	// ------------------------------------------------------------------
	// Setup GBuffer ----------------------------------------------------
	// ------------------------------------------------------------------
	// ------------------------------------------------------------------

	/*GLClearErrors();

	// ------------------------------------------------------------------
	// Setup framebuffer
	// Create framebuffer
	glGenFramebuffers(1, &gBuffer);
	// Bind the current framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	// ------------------------------------------------------------------

	// ------------------------------------------------------------------
	// Setup buffers for position, normal, albedo and specular intensity

	// Position color buffer
	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	// Create the texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, nullptr);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	// Normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	// Create the texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, nullptr);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	// Color and specular color buffer
	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	// Create the texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

	glGenTextures(1, &gAlbedoSpec2);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec2);
	// Create the texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gAlbedoSpec2, 0);

	// Normal color buffer2
	glGenTextures(1, &gNormal2);
	glBindTexture(GL_TEXTURE_2D, gNormal2);
	// Create the texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, nullptr);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, gNormal2, 0);

	// ------------------------------------------------------------------
	// Specify a list of color buffers to draw to
	GLuint attachments[5] = { GL_COLOR_ATTACHMENT0, 
		GL_COLOR_ATTACHMENT1, 
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4
	};
	glDrawBuffers(5, attachments);

	GLErrorCheck("Framebuffer setup error.!!!!!!!!!!!!!!!!!");

	// ------------------------------------------------------------------
	// Create a depth buffer
	
	GLClearErrors();

	GLuint rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	// Create the renderbuffer storage
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Attach the render buffer to the framebuffer as a depth attachement
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	// ------------------------------------------------------------------
	// Check the framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer not complete." << std::endl;
	}

	// ------------------------------------------------------------------
	// Deactivate the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLErrorCheck("FramebufferDepth setup error.!!!!!!!!!!!!!!!!!");

	// ------------------------------------------------------------------
	// ------------------------------------------------------------------
	// End setup GBuffer ------------------------------------------------
	// ------------------------------------------------------------------
	// ------------------------------------------------------------------*/

	GLErrorCheck("TestGLApp::SetupScene");
}

void 
TestGLApp::LoadShaders()
{
	GLClearErrors();

	// Initialize shaders
	//m_pBlinnPhongShader = new Engine::Shader(".\\Shaders\\simple.vert", ".\\Shaders\\simple.frag");
	//m_pReflectionShader		= new Engine::Shader(".\\Shaders\\reflection.vert", ".\\Shaders\\reflection.frag");
	//m_pQuadShader			= new Engine::Shader(".\\Shaders\\quadRender.vert", ".\\Shaders\\quadRender.frag");
	//m_pNormalShader			= new Engine::Shader(".\\Shaders\\normalMapping.vert", ".\\Shaders\\normalMapping.frag");
	//m_pParallaxShader		= new Engine::Shader(".\\Shaders\\normalMapping.vert", ".\\Shaders\\normalMapping.frag");
	
	//m_pBlinnPhongShader		= new Engine::Shader(".\\Shaders\\blinnPhongSolid.vert", ".\\Shaders\\blinnPhongSolid.frag");
	
	//m_pHDRShader			= new Engine::Shader(".\\Shaders\\hdr.vert", ".\\Shaders\\hdr.frag");
	
	//m_pGBufferShaderNormal = new Engine::Shader(".\\Shaders\\gbuffer.vert", ".\\Shaders\\gbufferNormal.frag");
	//m_pGBufferShaderParallax = new Engine::Shader(".\\Shaders\\gbuffer.vert", ".\\Shaders\\gbufferParallax.frag");
	//m_pLightingPassShader	= new Engine::Shader(".\\Shaders\\lightingPassDeferred.vert", ".\\Shaders\\lightingPassDeferred.frag");

	// Add shaders to shaderman
	//ShaderMan::Instance().AddShader(m_pBlinnPhongShader);
	//ShaderMan::Instance().AddShader(m_pReflectionShader);
	//ShaderMan::Instance().AddShader(m_pQuadShader);
	//ShaderMan::Instance().AddShader(m_pNormalShader);
	//ShaderMan::Instance().AddShader(m_pParallaxShader);
	//ShaderMan::Instance().AddShader(m_pHDRShader);
	//ShaderMan::Instance().AddShader(m_pGBufferShaderNormal);
	//ShaderMan::Instance().AddShader(m_pGBufferShaderParallax);
	//ShaderMan::Instance().AddShader(m_pLightingPassShader);

	GLErrorCheck("TestGLApp::LoadShaders");
}

void 
TestGLApp::Update(float dt)
{
	GLClearErrors();

	BaseGLApp::Update(dt);

	// Update PBR material
	m_pbrMaterial.ao = MappedProperties::GetInstance().getFloatProperty("ambientOcclusion");
	m_pbrMaterial.metallic = MappedProperties::GetInstance().getFloatProperty("metallic");
	m_pbrMaterial.roughness = MappedProperties::GetInstance().getFloatProperty("roughness");
	m_pbrMaterial.albedo.x = MappedProperties::GetInstance().getFloatProperty("albedoX");
	m_pbrMaterial.albedo.y = MappedProperties::GetInstance().getFloatProperty("albedoY");
	m_pbrMaterial.albedo.z = MappedProperties::GetInstance().getFloatProperty("albedoZ");

	// Get object
	GL::Object* planet36Object = ObjectMan::GetInstance().getObject("planet36");
	if (planet36Object != nullptr)
		planet36Object->setPBRMaterial(&m_pbrMaterial);

	// Update light position
	m_pointLightStruct1.Position.x = MappedProperties::GetInstance().getFloatProperty("pointLight1PosX");
	m_pointLightStruct1.Position.y = MappedProperties::GetInstance().getFloatProperty("pointLight1PosY");
	m_pointLightStruct1.Position.z = MappedProperties::GetInstance().getFloatProperty("pointLight1PosZ");

	m_pointLightStruct1.Attenuation.x = MappedProperties::GetInstance().getFloatProperty("pointLight1AttX");
	m_pointLightStruct1.Attenuation.y = MappedProperties::GetInstance().getFloatProperty("pointLight1AttY");
	m_pointLightStruct1.Attenuation.z = MappedProperties::GetInstance().getFloatProperty("pointLight1AttZ");

	m_pPBRTechnique->setPointLight(m_pointLightStruct1);

	m_pointLightStruct2.Position.x = MappedProperties::GetInstance().getFloatProperty("pointLight2PosX");
	m_pointLightStruct2.Position.y = MappedProperties::GetInstance().getFloatProperty("pointLight2PosY");
	m_pointLightStruct2.Position.z = MappedProperties::GetInstance().getFloatProperty("pointLight2PosZ");
	m_pPhongTechnique->setPointLight(m_pointLightStruct2);

	TechniqueMan::Instance().update();

	//m_pSkybox->Update();
	GfxStats::Instance().Update(dt);

	GLErrorCheck("TestGLApp::Update");
}

void 
TestGLApp::Draw(float dt)
{
	// ---------------------------------------------------------------------------
	GLClearErrors();

	// Standard rendering 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Object* quadPhong0 = ObjectMan::GetInstance().GetObject("quadPhong0");
	//quadPhong0->Render();

	ObjectMan::GetInstance().renderAll(dt);

	//// ---------------------------------------------------------------------------
	//GLClearErrors();

	//// ---------------------------------------------------------------------------
	//// ---------------------------------------------------------------------------
	//// Deferred rendering --------------------------------------------------------
	//// ---------------------------------------------------------------------------
	//// ---------------------------------------------------------------------------
	//// Step 1 - geometry pass - render to gbuffer

	//GLClearErrors();

	//// Bind the 
	//glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//pGBufferTechniqueNormal->SetEyePosWorld(CameraMan::Instance().GetActiveCamera()->GetCameraPosition());
	////pGBufferTechniqueParallax->SetEyePosWorld(CameraMan::Instance().GetActiveCamera()->GetCameraPosition());

	//// Render the object
	//Engine::Object* objectNormal = ObjectMan::GetInstance().GetObject("groundNormal");
	///*Engine::Object* objectParallax = ObjectMan::GetInstance().GetObject("groundParallax");

	//Engine::Object* object1 = ObjectMan::GetInstance().GetObject("ground4");
	//Engine::Object* object2 = ObjectMan::GetInstance().GetObject("ground");
	//Engine::Object* object3 = ObjectMan::GetInstance().GetObject("ground2");
	//Engine::Object* object4 = ObjectMan::GetInstance().GetObject("ground3");
	//Engine::Object* object5 = ObjectMan::GetInstance().GetObject("ground5");*/
	//
	////pGBufferTechniqueNormal->SetDisplacementMapProperties(0.02f);
	//objectNormal->Render(m_pGBufferShaderNormal);
	////pGBufferTechniqueParallax->SetDisplacementMapProperties(0.07f);
	////objectParallax->Render(m_pGBufferShaderParallax);

	////pGBufferTechnique->SetDisplacementMapProperties(0.02f);
	////object1->Render(m_pGBufferShader);
	////pGBufferTechnique->SetDisplacementMapProperties(0.07f);
	////object2->Render(m_pGBufferShader);

	////pGBufferTechnique->SetDisplacementMapProperties(0.07f);
	////object3->Render(m_pGBufferShader);
	////pGBufferTechnique->SetDisplacementMapProperties(0.07f);
	////object4->Render(m_pGBufferShader);
	////pGBufferTechnique->SetDisplacementMapProperties(0.2f);
	////object5->Render(m_pGBufferShader);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//GLErrorCheck("GBuffer render error.!!!!!!!!!!!!!!!!!");

	//// ---------------------------------------------------------------------------
	//// Step 2 - Lighting pass - Render to texture - HDR + tone mapping
	//GLClearErrors();

	//m_pHDRRenderToTexture->BindFramebuffer();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//m_pLightingPassShader->Enable();

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, gPosition);
	//GLuint gPositionLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gPosition");
	//glUniform1i(gPositionLocation, 0);

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	//GLuint gNormalLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gAlbedoSpec");
	//glUniform1i(gNormalLocation, 1);

	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, gNormal);
	//GLuint gAlbedoSpecLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gNormal");
	//glUniform1i(gAlbedoSpecLocation, 2);

	//glActiveTexture(GL_TEXTURE3);
	//glBindTexture(GL_TEXTURE_2D, gAlbedoSpec2);
	//GLuint gAlbedoSpec2Location = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gAlbedoSpec2");
	//glUniform1i(gAlbedoSpec2Location, 3);

	//glActiveTexture(GL_TEXTURE4);
	//glBindTexture(GL_TEXTURE_2D, gNormal2);
	//GLuint gNormal2Location = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gNormal2");
	//glUniform1i(gNormal2Location, 4);

	//GLuint gEyePosWLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "eyePosW");
	//glUniform3fv(gEyePosWLocation, 1, &CameraMan::Instance().GetActiveCamera()->GetCameraPosition()[0]);
	//
	//m_pHDRRenderToTexture->RenderToQuad();

	//m_pLightingPassShader->Disable();

	//m_pHDRRenderToTexture->UnbindFramebuffer();

	//GLErrorCheck("Render lighting pass error.!!!!!!!!!!!!!!!!!");

	//// ---------------------------------------------------------------------------
	//// Render texture to screen
	//GLClearErrors();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//m_pHDRShader->Enable();

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_pHDRRenderToTexture->GetColorBuffer());
	//m_pHDRRenderToTexture->RenderToQuad();

	//m_pHDRShader->Disable();
	//GLErrorCheck("Render texture to screen error.!!!!!!!!!!!!!!!!!");

	// ---------------------------------------------------------------------------

	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------
	// Deferred rendering end ----------------------------------------------------
	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------

	// ---------------------------------------------------------------------------

	//// Rendering to texture
	////glBindFramebuffer(GL_FRAMEBUFFER, uiFBO);
	////
	////	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////	// Draw calls
	////	ObjectMan::GetInstance().RenderObject("SphereObject");

	////glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//// Draw calls
	////m_pSkybox->Draw();

	// ---------------------------------------------------------------------------
	// Render UI
	//UIManager::Instance().render();
	GfxStats::Instance().Display(dt);

	// ---------------------------------------------------------------------------
	// Swap buffers
	glfwSwapBuffers(Core::Window);

	// ---------------------------------------------------------------------------
	GLErrorCheck("TestGLApp::Draw");

	// ---------------------------------------------------------------------------
}