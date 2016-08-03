#include "MyEngine.h"

// Rendering engine include
#include "Common.h"
#include "GfxStats.h"
#include "ObjectMan.h"


MyEngine::MyEngine(void)
{
	m_pBlinnPhongShader				= nullptr;
	m_pReflectionShader				= nullptr;
	m_pNormalShader					= nullptr;
	m_pQuadShader					= nullptr;
	m_pHDRShader					= nullptr;

	pDirectionalLightTechnique		= nullptr;
	pReflectionTechnique			= nullptr;
	pNormalMappingTechnique			= nullptr;
	pBlinnPhongSolidTechnique		= nullptr;
	m_pSkybox						= nullptr;
	pHDRLightTechnique				= nullptr;
	pGBufferTechnique				= nullptr;

	m_pHDRRenderToTexture			= nullptr;
	m_pShadowMappingRenderToTexture = nullptr;
}


MyEngine::~MyEngine(void)
{
	if (pDirectionalLightTechnique != nullptr)
	{
		delete pDirectionalLightTechnique;
		pDirectionalLightTechnique = nullptr;
	}

	if (pReflectionTechnique != nullptr)
	{
		delete pReflectionTechnique;
		pReflectionTechnique = nullptr;
	}

	if (pNormalMappingTechnique != nullptr)
	{
		delete pNormalMappingTechnique;
		pNormalMappingTechnique = nullptr;
	}

	if (pBlinnPhongSolidTechnique != nullptr)
	{
		delete pBlinnPhongSolidTechnique;
		pBlinnPhongSolidTechnique = nullptr;
	}

	if (pHDRLightTechnique != nullptr)
	{
		delete pHDRLightTechnique;
		pHDRLightTechnique = nullptr;
	}

	if (pGBufferTechnique != nullptr)
	{
		delete pGBufferTechnique;
		pGBufferTechnique = nullptr;
	}
	
	if (m_pSkybox != NULL)
	{
		delete m_pSkybox;
		m_pSkybox = NULL;
	}

	if (m_pHDRRenderToTexture != nullptr)
	{
		delete m_pHDRRenderToTexture;
		m_pHDRRenderToTexture = nullptr;
	}

	if (m_pShadowMappingRenderToTexture != nullptr)
	{
		delete m_pShadowMappingRenderToTexture;
		m_pShadowMappingRenderToTexture = nullptr;
	}
}

// Overrides
int 
MyEngine::Initialize()
{
	GLClearErrors();

	AbstractEngine::Initialize();

	SetupScene();

	GLErrorCheck("MyEngine::Initialize");

	// Success
	return 1;
}

void 
MyEngine::SetupScene()
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

	Engine::Object* groundObject = new Engine::Object("ground",
		".\\Assets\\quad.obj",
		m_pNormalShader,
		new Engine::Texture(".\\Assets\\brick_diffuse.jpg", TextureType::Diffuse, true, false),
		new Engine::Texture(".\\Assets\\brick_normal.jpg", TextureType::Normal, true, false),
		new Engine::Texture(".\\Assets\\brick_displacement.jpg", TextureType::Displacement, true, false),
		new Engine::Texture(".\\Assets\\brick_specular.jpg", TextureType::Specular, true, false));
	groundObject->Scale(100.0f, 1.0f, 100.0f);
	groundObject->Translate(0, -100.0f, 0);

	ObjectMan::GetInstance().AddObject(groundObject);

	// ------------------------------------------------------------------

	Engine::Object* groundObject2 = new Engine::Object("ground2",
		".\\Assets\\quad.obj",
		m_pNormalShader,
		new Engine::Texture(".\\Assets\\bricks.jpg", TextureType::Diffuse, true, false),
		new Engine::Texture(".\\Assets\\bricks_normal.jpg", TextureType::Normal, true, false),
		new Engine::Texture(".\\Assets\\bricks_disp_inv.png", TextureType::Displacement, true, false));
	groundObject2->Scale(100.0f, 1.0f, 100.0f);
	groundObject2->Translate(0.0f, 0.0f, 250.0f);

	ObjectMan::GetInstance().AddObject(groundObject2);

	// ------------------------------------------------------------------

	Engine::Object* groundObject3 = new Engine::Object("ground3",
		".\\Assets\\quad.obj",
		m_pNormalShader,
		new Engine::Texture(".\\Assets\\bricks2.jpg", TextureType::Diffuse, true, false),
		new Engine::Texture(".\\Assets\\bricks2_normal.jpg", TextureType::Normal, true, false),
		new Engine::Texture(".\\Assets\\bricks2_disp_inv.jpg", TextureType::Displacement, true, false));
	groundObject3->Scale(100.0f, 1.0f, 100.0f);
	groundObject3->Translate(250.0f, 0.0f, 0.0f);

	ObjectMan::GetInstance().AddObject(groundObject3);

	// ------------------------------------------------------------------

	Engine::Object* groundObject4 = new Engine::Object("ground4",
		".\\Assets\\quad.obj",
		m_pBlinnPhongShader,
		new Engine::Texture(".\\Assets\\bricks2.jpg", TextureType::Diffuse, true, false), 
		new Engine::Texture(".\\Assets\\bricks2_normal.jpg", TextureType::Normal, true, false),
		new Engine::Texture(".\\Assets\\bricks2_disp_inv.jpg", TextureType::Displacement, true, false),
		new Engine::Texture(".\\Assets\\bricks2_disp_inv.jpg", TextureType::Specular, true, false));
	groundObject4->Scale(100.0f, 1.0f, 100.0f);
	groundObject4->Translate(250.0f, -100.0f, 250.0f);

	ObjectMan::GetInstance().AddObject(groundObject4);

	// ------------------------------------------------------------------

	Engine::Object* groundObject5 = new Engine::Object("ground5",
		".\\Assets\\quad.obj",
		m_pNormalShader,
		new Engine::Texture(".\\Assets\\wood.png", TextureType::Diffuse, true, false),
		new Engine::Texture(".\\Assets\\wood_normal.png", TextureType::Normal, true, false),
		new Engine::Texture(".\\Assets\\wood_disp_inv.png", TextureType::Displacement, true, false));
	groundObject5->Scale(100.0f, 1.0f, 100.0f);
	groundObject5->Translate(500.0f, 0.0f, 0.0f);

	ObjectMan::GetInstance().AddObject(groundObject5);

	// ------------------------------------------------------------------

	// Skybox
	const char* szSkyboxFiles[] = { ".\\Assets\\skybox\\right.bmp",
		".\\Assets\\skybox\\left.bmp",
		".\\Assets\\skybox\\top.bmp",
		".\\Assets\\skybox\\bottom.bmp",
		".\\Assets\\skybox\\front.bmp",
		".\\Assets\\skybox\\back.bmp" };
	m_pSkybox = new Skybox();
	m_pSkybox->LoadCubeMap(&szSkyboxFiles[0]);

	// ------------------------------------------------------------------

	// Create camera
	/*CameraMan::Instance().CreateCamera("Cam1", (float)M_PI_4, 0.1f, 3000.0f);
	CameraMan::Instance().GetCamera("Cam1")->SetPosition(glm::vec3(61.4116f, 303.988f, -251.391f));
	CameraMan::Instance().GetCamera("Cam1")->SetTarget(glm::vec3(61.6961f, 303.262f, -250.765f));
	CameraMan::Instance().GetCamera("Cam1")->SetUp(glm::vec3(0.300814f, 0.687144f, 0.66132f));*/

	CameraMan::Instance().CreateCamera("Cam1", (float)M_PI_4, 0.1f, 3000.0f);
	CameraMan::Instance().GetCamera("Cam1")->SetPosition(glm::vec3(0.0f, 50.0f, 0.0f));
	CameraMan::Instance().GetCamera("Cam1")->SetTarget(glm::vec3(1.0f, 0.0f, 0.0f));
	CameraMan::Instance().GetCamera("Cam1")->SetUp(glm::vec3(0.0f, 1.0f, 0.0f));

	// ------------------------------------------------------------------

	// Lighting
	// Directional light definition
	DirectionalLight dirLightStruct;
	dirLightStruct.AmbientLight			= glm::vec3(1.3f, 1.3f, 1.3f);
	dirLightStruct.DiffuseLight			= glm::vec3(0.5f, 0.5f, 0.5f);
	dirLightStruct.Position				= glm::vec3(-0.2f, -1.0f, -0.3f);
	dirLightStruct.SpecularLight		= glm::vec3(1.0f, 1.0f, 1.0f);
	dirLightStruct.SpecularIntensity	= 0.3f;

	// Point light definition
	PointLight pointLightStruct1;
	pointLightStruct1.AmbientLight = glm::vec3(10.0f, 10.0f, 10.0f);
	pointLightStruct1.DiffuseLight = glm::vec3(100.0f, 100.0f, 100.0f);
	pointLightStruct1.Position = glm::vec3(200.0f, 5.0f, 250.0f);
	pointLightStruct1.SpecularLight = glm::vec3(100.0f, 100.0f, 100.0f);
	pointLightStruct1.SpecularIntensity = 10.0f;

	PointLight pointLightStruct2;
	pointLightStruct2.AmbientLight = glm::vec3(10.0f, 5.0f, 10.0f);
	pointLightStruct2.DiffuseLight		= glm::vec3(100.0f, 50.0f, 200.0f);
	pointLightStruct2.Position			= glm::vec3(300.0f, 5.0f, 250.0f);
	pointLightStruct2.SpecularLight		= glm::vec3(1.0f, 1.0f, 1.0f);
	pointLightStruct2.SpecularIntensity = 0.2f;

	// Material definition
	Material planeMaterialChromeStruct;
	planeMaterialChromeStruct.Ambient		= glm::vec3(0.1f, 0.1f, 0.1f);
	planeMaterialChromeStruct.Diffuse		= glm::vec3(0.8f, 0.0f, 0.2f);
	planeMaterialChromeStruct.Emission		= glm::vec3(0.1f, 0.7f, 0.9f);
	planeMaterialChromeStruct.Specular		= glm::vec3(1.0f, 1.0f, 1.0f);
	planeMaterialChromeStruct.Shineness		= 32.0f;
	
	// Simple shader

	// Create light techniques
	/*pDirectionalLightTechnique = new LightTechnique(m_pBlinnPhongShader);
	pDirectionalLightTechnique->SetDirectionalLight(dirLightStruct);
	pDirectionalLightTechnique->SetMaterial(materialStruct);*/

	pDirectionalLightTechnique = new LightTechnique(m_pLightingPassShader);
	pDirectionalLightTechnique->SetDirectionalLight(dirLightStruct);
	pDirectionalLightTechnique->SetMaterial(planeMaterialChromeStruct);

	pGBufferTechnique = new LightTechnique(m_pGBufferShader);
	pGBufferTechnique->SetDisplacementMapProperties(0.03f);

	// Reflection shader
	//pReflectionTechnique = new LightTechnique(m_pReflectionShader);
	//pReflectionTechnique->SetCubeMap(m_pSkybox->GetSkyboxTextureHandle());

	// Normal mapping shader
	pNormalMappingTechnique = new LightTechnique(m_pNormalShader);
	pNormalMappingTechnique->SetDirectionalLight(dirLightStruct);
	pNormalMappingTechnique->AddPointLight(pointLightStruct1);
	pNormalMappingTechnique->AddPointLight(pointLightStruct2);
	pNormalMappingTechnique->SetMaterial(planeMaterialChromeStruct);
	pNormalMappingTechnique->SetGamma(2.2f);
	pNormalMappingTechnique->SetDisplacementMapProperties(0.05f);

	// Blinn-Phong solid shader
	pBlinnPhongSolidTechnique = new LightTechnique(m_pBlinnPhongShader);
	pBlinnPhongSolidTechnique->SetDirectionalLight(dirLightStruct);
	pBlinnPhongSolidTechnique->AddPointLight(pointLightStruct1);
	pBlinnPhongSolidTechnique->AddPointLight(pointLightStruct2);
	pBlinnPhongSolidTechnique->SetMaterial(planeMaterialChromeStruct);
	pBlinnPhongSolidTechnique->SetGamma(2.2f);

	// ------------------------------------------------------------------

	m_pHDRRenderToTexture = new RenderToTexture();
	m_pHDRRenderToTexture->SetupFramebuffer(GL_RGB16F, GL_FLOAT, true, false);
	m_pHDRRenderToTexture->SetupQuadGeometry();

	pHDRLightTechnique = new HDRLightingTechnique(m_pHDRShader);
	pHDRLightTechnique->SetExposure(0.2f);
	pHDRLightTechnique->SetHDREnabled(GL_TRUE);
	pHDRLightTechnique->SetGamma(2.2f);

	// ------------------------------------------------------------------

	m_pShadowMappingRenderToTexture = new RenderToTexture();
	m_pShadowMappingRenderToTexture->SetupFramebuffer(GL_RGB16F, GL_FLOAT, false, true);
	m_pShadowMappingRenderToTexture->SetupQuadGeometry();

	// ------------------------------------------------------------------
	// ------------------------------------------------------------------
	// Setup GBuffer ----------------------------------------------------
	// ------------------------------------------------------------------
	// ------------------------------------------------------------------

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	// Normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	// Create the texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	// Color and specular color buffer
	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	// Create the texture memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	// Setup texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Attach the texture to the framebuffer as a color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

	// ------------------------------------------------------------------
	// Specify a list of color buffers to draw to
	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, 
		GL_COLOR_ATTACHMENT1, 
		GL_COLOR_ATTACHMENT2
	};
	glDrawBuffers(3, attachments);

	// ------------------------------------------------------------------
	// Create a depth buffer
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

	// ------------------------------------------------------------------
	// ------------------------------------------------------------------
	// End setup GBuffer ------------------------------------------------
	// ------------------------------------------------------------------
	// ------------------------------------------------------------------

	GLErrorCheck("MyEngine::SetupScene");
}

void 
MyEngine::LoadShaders()
{
	GLClearErrors();

	// Initialize shaders
	//m_pBlinnPhongShader = new Engine::Shader(".\\Shaders\\simple.vert", ".\\Shaders\\simple.frag");
	m_pReflectionShader		= new Engine::Shader(".\\Shaders\\reflection.vert", ".\\Shaders\\reflection.frag");
	m_pQuadShader			= new Engine::Shader(".\\Shaders\\quadRender.vert", ".\\Shaders\\quadRender.frag");
	m_pNormalShader			= new Engine::Shader(".\\Shaders\\normalMapping.vert", ".\\Shaders\\normalMapping.frag");
	m_pBlinnPhongShader		= new Engine::Shader(".\\Shaders\\blinnPhongSolid.vert", ".\\Shaders\\blinnPhongSolid.frag");
	m_pHDRShader			= new Engine::Shader(".\\Shaders\\hdr.vert", ".\\Shaders\\hdr.frag");
	m_pGBufferShader		= new Engine::Shader(".\\Shaders\\gbuffer.vert", ".\\Shaders\\gbuffer.frag");
	m_pLightingPassShader	= new Engine::Shader(".\\Shaders\\lightingPassDeferred.vert", ".\\Shaders\\lightingPassDeferred.frag");

	// Add shaders to shaderman
	ShaderMan::Instance().AddShader(m_pBlinnPhongShader);
	ShaderMan::Instance().AddShader(m_pReflectionShader);
	ShaderMan::Instance().AddShader(m_pQuadShader);
	ShaderMan::Instance().AddShader(m_pNormalShader);
	ShaderMan::Instance().AddShader(m_pHDRShader);
	ShaderMan::Instance().AddShader(m_pGBufferShader);
	ShaderMan::Instance().AddShader(m_pLightingPassShader);

	GLErrorCheck("MyEngine::LoadShaders");
}

void 
MyEngine::Update(float dt)
{
	GLClearErrors();

	AbstractEngine::Update(dt);

	//m_pSkybox->Update();
	GfxStats::Instance().Update(dt);

	GLErrorCheck("MyEngine::Update");
}

void 
MyEngine::Draw(float dt)
{
	// ---------------------------------------------------------------------------
	GLClearErrors();

	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------
	// Deferred rendering --------------------------------------------------------
	// ---------------------------------------------------------------------------
	// ---------------------------------------------------------------------------
	// Step 1 - geometry pass - render to gbuffer

	// Bind the 
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pGBufferTechnique->SetEyePosWorld(CameraMan::Instance().GetActiveCamera()->GetCameraPosition());

	// Render the object
	Engine::Object* object1 = ObjectMan::GetInstance().GetObject("ground4");
	Engine::Object* object2 = ObjectMan::GetInstance().GetObject("ground");
	Engine::Object* object3 = ObjectMan::GetInstance().GetObject("ground2");
	Engine::Object* object4 = ObjectMan::GetInstance().GetObject("ground3");
	Engine::Object* object5 = ObjectMan::GetInstance().GetObject("ground5");
	
	pGBufferTechnique->SetDisplacementMapProperties(0.02f);
	object1->Render(m_pGBufferShader);
	pGBufferTechnique->SetDisplacementMapProperties(0.07f);
	object2->Render(m_pGBufferShader);

	pGBufferTechnique->SetDisplacementMapProperties(0.07f);
	object3->Render(m_pGBufferShader);
	pGBufferTechnique->SetDisplacementMapProperties(0.07f);
	object4->Render(m_pGBufferShader);
	pGBufferTechnique->SetDisplacementMapProperties(0.2f);
	object5->Render(m_pGBufferShader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ---------------------------------------------------------------------------
	// Step 2 - Lighting pass - Render to texture - HDR + tone mapping
	m_pHDRRenderToTexture->BindFramebuffer();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pLightingPassShader->Enable();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	GLuint gPositionLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gPosition");
	glUniform1i(gPositionLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	GLuint gNormalLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gNormal");
	glUniform1i(gNormalLocation, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	GLuint gAlbedoSpecLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "gAlbedoSpec");
	glUniform1i(gAlbedoSpecLocation, 2);

	GLuint gEyePosWLocation = glGetUniformLocation(m_pLightingPassShader->ProgramID(), "eyePosW");
	glUniform3fv(gEyePosWLocation, 1, &CameraMan::Instance().GetActiveCamera()->GetCameraPosition()[0]);
	
	m_pHDRRenderToTexture->RenderToQuad();

	GfxStats::Instance().Display(dt);

	m_pLightingPassShader->Disable();

	m_pHDRRenderToTexture->UnbindFramebuffer();

	// ---------------------------------------------------------------------------
	// Render texture to screen

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pHDRShader->Enable();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pHDRRenderToTexture->GetColorBuffer());
	m_pHDRRenderToTexture->RenderToQuad();

	m_pHDRShader->Disable();

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
	// Swap buffers
	glfwSwapBuffers(Core::Window);

	// ---------------------------------------------------------------------------
	GLErrorCheck("MyEngine::Draw");

	// ---------------------------------------------------------------------------
}