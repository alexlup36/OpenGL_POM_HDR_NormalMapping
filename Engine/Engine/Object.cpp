#include "Object.h"

#include "TransformTechnique.h"
#include "Camera.h"
#include "CameraMan.h"
#include "ObjectMan.h"

namespace GL
{
	// ----------------------------------------------------------------------------

	Object::Object(const std::string& name,
		const std::string& modelPath,
		BaseTechnique* technique,
		Texture* diffuseTex /*= nullptr*/,
		Texture* diffuseTex2 /*= nullptr*/,
		Texture* normalTex /*= nullptr*/,
		Texture* normalTex2 /*= nullptr*/,
		Texture* displacementTex /*= nullptr*/,
		Texture* specularTex /*= nullptr*/)
		: Name(name),
		m_sModelPath(modelPath),
		m_pCurrentTechnique(technique),
		m_pTexNormal(normalTex),
		m_pTexNormal2(normalTex2),
		m_pTexDiffuse(diffuseTex),
		m_pTexDiffuse2(diffuseTex2),
		m_pTexDisplacement(displacementTex),
		m_pTexSpecular(specularTex),
		m_bEnablePBR(false),
		m_bIsUI(false)
	{
		LoadMesh();
		initTextureUniformLocation();

		m_pTransform = new Transform();
	}

	// ----------------------------------------------------------------------------

	Object::Object(const std::string& name,
		const std::string& modelPath,
		BaseTechnique* technique,
		Material* material)
		: Name(name),
		m_sModelPath(modelPath),
		m_pCurrentTechnique(technique),
		m_pMaterial(*material),
		m_bEnablePBR(false),
		m_bIsUI(false)
	{
		LoadMesh();
		initMaterialUniformLocation();

		m_pTransform = new Transform();

		Init();
	}

	// ----------------------------------------------------------------------------

	Object::Object(const std::string& name,
		const std::string& modelPath,
		BaseTechnique* technique,
		Material* material,
		bool ui)
		: Name(name),
		m_sModelPath(modelPath),
		m_pCurrentTechnique(technique),
		m_pMaterial(*material),
		m_bEnablePBR(false),
		m_bIsUI(ui)
	{
		LoadMesh();
		initMaterialUniformLocation();

		m_pTransform = new Transform();

		Init();
	}

	// ----------------------------------------------------------------------------

	Object::Object(const std::string& name,
		const std::string& modelPath,
		BaseTechnique* technique,
		PBRMaterial* material)
		: Name(name),
		m_sModelPath(modelPath),
		m_pCurrentTechnique(technique),
		m_pbrMaterial(*material),
		m_bEnablePBR(true),
		m_bIsUI(false)
	{
		LoadMesh();
		initPBRMaterialUniformLocation();

		m_pTransform = new Transform();

		Init();
	}

	// ----------------------------------------------------------------------------

	Object::Object(const std::string& name,
		const std::string& modelPath,
		BaseTechnique* technique,
		PBRTexMaterial* material)
		: Name(name),
		m_sModelPath(modelPath),
		m_pCurrentTechnique(technique),
		m_pbrTexMaterial(*material),
		m_bEnablePBR(true),
		m_bIsUI(false)
	{
		LoadMesh();
		initPBRMaterialUniformLocation();

		m_pTransform = new Transform();

		Init();
	}

	// ----------------------------------------------------------------------------

	Object::~Object(void)
	{
		// Delete the transform object
		if (m_pTransform != nullptr)
		{
			delete m_pTransform;
			m_pTransform = nullptr;
		}

		// Delete textures
		if (m_pTexDiffuse != nullptr)
		{
			delete m_pTexDiffuse;
			m_pTexDiffuse = nullptr;
		}
		if (m_pTexDiffuse2 != nullptr)
		{
			delete m_pTexDiffuse2;
			m_pTexDiffuse2 = nullptr;
		}
		if (m_pTexNormal != nullptr)
		{
			delete m_pTexNormal;
			m_pTexNormal = nullptr;
		}
		if (m_pTexNormal2 != nullptr)
		{
			delete m_pTexNormal2;
			m_pTexNormal2 = nullptr;
		}
		if (m_pTexDisplacement != nullptr)
		{
			delete m_pTexDisplacement;
			m_pTexDisplacement = nullptr;
		}
		if (m_pTexSpecular != nullptr)
		{
			delete m_pTexSpecular;
			m_pTexSpecular = nullptr;
		}

		// Delete the list of meshes attached to this object
		while (!m_pMeshList.empty())
		{
			delete m_pMeshList.back();
			m_pMeshList.pop_back();
		}
	}

	// ----------------------------------------------------------------------------

	void Object::Init()
	{
		m_pTexDiffuse = nullptr;
		m_pTexDiffuse2 = nullptr;
		m_pTexNormal = nullptr;
		m_pTexNormal2 = nullptr;
		m_pTexDisplacement = nullptr;
		m_pTexSpecular = nullptr;
	}

	// ----------------------------------------------------------------------------

	void Object::render()
	{
		// Set the shader material
		m_bEnablePBR ? setPBRShaderMaterial() : setShaderMaterial();
		// Bind the texture attached to the object
		bindTextures();
		// Go through the meshes and render them
		renderMeshes();
	}

	// ----------------------------------------------------------------------------

	void Object::setMaterial(Material* newMaterial)
	{
		if (newMaterial != nullptr)
		{
			m_pMaterial.Ambient = newMaterial->Ambient;
			m_pMaterial.Diffuse = newMaterial->Diffuse;
			m_pMaterial.Emission = newMaterial->Emission;
			m_pMaterial.Shineness = newMaterial->Shineness;
			m_pMaterial.Specular = newMaterial->Specular;
		}
	}

	// ----------------------------------------------------------------------------

	void Object::setPBRMaterial(PBRMaterial* newMaterial)
	{
		if (newMaterial != nullptr)
		{
			m_pbrMaterial.albedo = newMaterial->albedo;
			m_pbrMaterial.ao = newMaterial->ao;
			m_pbrMaterial.metallic = newMaterial->metallic;
			m_pbrMaterial.roughness = newMaterial->roughness;
		}
	}

	// ----------------------------------------------------------------------------

	void Object::setShaderMaterial()
	{
		glUniform3f(m_materialUniformLocation.ambientCompLoc, m_pMaterial.Ambient.x, m_pMaterial.Ambient.y, m_pMaterial.Ambient.z);
		glUniform3f(m_materialUniformLocation.diffuseCompLoc, m_pMaterial.Diffuse.x, m_pMaterial.Diffuse.y, m_pMaterial.Diffuse.z);
		glUniform3f(m_materialUniformLocation.specularCompLoc, m_pMaterial.Specular.x, m_pMaterial.Specular.y, m_pMaterial.Specular.z);
		glUniform1f(m_materialUniformLocation.shinenessLoc, m_pMaterial.Shineness);
	}

	// ----------------------------------------------------------------------------

	void Object::setPBRShaderMaterial()
	{
		glUniform3f(m_pbrMaterialUniformLocation.albedoLoc, m_pbrMaterial.albedo.x, m_pbrMaterial.albedo.y, m_pbrMaterial.albedo.z);
		glUniform1f(m_pbrMaterialUniformLocation.aoLoc, m_pbrMaterial.ao);
		glUniform1f(m_pbrMaterialUniformLocation.roughnessLoc, m_pbrMaterial.roughness);
		glUniform1f(m_pbrMaterialUniformLocation.metallicLoc, m_pbrMaterial.metallic);
	}

	// ----------------------------------------------------------------------------

	void Object::update(float dt)
	{
		// Get active camera
		Camera2* pActiveCamera = CameraMan::Instance().GetActiveCamera();

		glm::mat4 view = pActiveCamera->ViewMatrix();
		glm::mat4 projection;
		if (m_bIsUI == false)
			projection = pActiveCamera->ProjectionMatrix();
		else
			projection = pActiveCamera->OrthoProjectionMatrix();

		// Get model matrix
		glm::mat4 model = m_pTransform->GetModel();

		// Get current transform reference
		TransformTechnique* transformTechnique = dynamic_cast<TransformTechnique*>(m_pCurrentTechnique);
		// Set world matrix
		transformTechnique->setWMatrix(model);
		// Set view matrix
		transformTechnique->setViewMatrix(view);
		// Set projection matrix
		transformTechnique->setProjectionMatrix(projection);
		// Set world-view-projection matrix
		if (m_bIsUI == false)
			transformTechnique->setWVPMatrix(projection * view * model);
		else
			transformTechnique->setWVPMatrix(projection * model);
		// Set normal matrix
		transformTechnique->setNMatrix(glm::transpose(glm::inverse(model)));
	}

	// ----------------------------------------------------------------------------

	void Object::initMaterialUniformLocation()
	{
		// Initialize uniform locations
		m_pCurrentTechnique->enable();

		GLuint programID = m_pCurrentTechnique->getProgramID();
		m_materialUniformLocation.emissionCompLoc = glGetUniformLocation(programID, "material.vMatEmission");
		m_materialUniformLocation.ambientCompLoc = glGetUniformLocation(programID, "material.vMatAmbient");
		m_materialUniformLocation.diffuseCompLoc = glGetUniformLocation(programID, "material.vMatDiffuse");
		m_materialUniformLocation.specularCompLoc = glGetUniformLocation(programID, "material.vMatSpecular");
		m_materialUniformLocation.shinenessLoc = glGetUniformLocation(programID, "material.fMatShineness");
	}

	// ----------------------------------------------------------------------------

	void Object::initPBRMaterialUniformLocation()
	{
		// Initialize uniform locations
		m_pCurrentTechnique->enable();

		GLuint programID = m_pCurrentTechnique->getProgramID();
	}

	// ----------------------------------------------------------------------------

	void Object::initTextureUniformLocation()
	{
		// Initialize uniform locations
		m_pCurrentTechnique->enable();

		m_textureUniformLocation.diffuseSampler0 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "diffuseSampler");
		m_textureUniformLocation.diffuseSampler1 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "diffuseSampler2");
		m_textureUniformLocation.normalSampler0 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "normalSampler");
		m_textureUniformLocation.normalSampler1 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "normalSampler2");
		m_textureUniformLocation.displacementSampler = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "displacementSampler");
		m_textureUniformLocation.specularSampler = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "specularSampler");
	}

	// ----------------------------------------------------------------------------

	//void Object::initTextureUniformLocation()
	//{
	//	// Initialize uniform locations
	//	m_pCurrentTechnique->enable();

	//	m_textureUniformLocation.diffuseSampler0 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "diffuseSampler");
	//	m_textureUniformLocation.diffuseSampler1 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "diffuseSampler2");
	//	m_textureUniformLocation.normalSampler0 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "normalSampler");
	//	m_textureUniformLocation.normalSampler1 = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "normalSampler2");
	//	m_textureUniformLocation.displacementSampler = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "displacementSampler");
	//	m_textureUniformLocation.specularSampler = glGetUniformLocation(m_pCurrentTechnique->getProgramID(), "specularSampler");
	//}

	// ----------------------------------------------------------------------------

	// Mesh processing
	void Object::LoadMesh()
	{
		// Use cached object mesh
		Object* cachedObject = ObjectMan::GetInstance().getObjectModel(m_sModelPath);
		if (cachedObject != nullptr)
		{
			auto& meshList = cachedObject->getMeshList();
			for each (Mesh* mesh in meshList)
			{
				Mesh* newMesh = new Mesh(mesh->getVertexArrayObject());
				newMesh->setVertexCount(mesh->getVertexCount());
				m_pMeshList.push_back(newMesh);
			}

			return;
		}

		Assimp::Importer assimpImporter;

		const aiScene* pScene = assimpImporter.ReadFile(m_sModelPath.c_str(),
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs |
			aiProcess_CalcTangentSpace);

		if (pScene == nullptr)
		{
			std::cout << "Mesh load failed!: " << m_sModelPath << " " << assimpImporter.GetErrorString() << std::endl;
			return;
		}
		else if (pScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || pScene->mRootNode == false)
		{
			std::cout << "Failed to load file " << m_sModelPath << " " << assimpImporter.GetErrorString() << std::endl;
			return;
		}
		else
		{
			std::cout << "Mesh loaded successfully: " << m_sModelPath << std::endl;
		}

		RecursiveProcess(pScene->mRootNode, pScene);
	}

	// ----------------------------------------------------------------------------

	void Object::ProcessMesh(aiMesh* pModel)
	{
		std::vector<Vertex> vertices;
		std::vector<GLushort> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < pModel->mNumVertices; i++)
		{
			// Vertex structure to be filled -------------------------------------------
			Vertex vertex;

			// Position ----------------------------------------------------------------
			glm::vec3 position;
			position.x = pModel->mVertices[i].x;
			position.y = pModel->mVertices[i].y;
			position.z = pModel->mVertices[i].z;
			vertex.position = position;

			// Normal ------------------------------------------------------------------
			glm::vec3 normal;
			if (pModel->HasNormals())
			{
				normal.x = pModel->mNormals[i].x;
				normal.y = pModel->mNormals[i].y;
				normal.z = pModel->mNormals[i].z;
				vertex.normal = normal;
			}
			else
			{
				vertex.normal = glm::vec3(0.0f);
			}

			// Texture coordinate ------------------------------------------------------
			glm::vec2 textureCoord;
			if (pModel->mTextureCoords[0])
			{
				textureCoord.x = pModel->mTextureCoords[0][i].x;
				textureCoord.y = pModel->mTextureCoords[0][i].y;
				vertex.textureCoord = textureCoord;
			}
			else
			{
				vertex.textureCoord = glm::vec2(0.0f, 0.0f);
			}

			// Tangent -----------------------------------------------------------------
			glm::vec3 tangent;
			if (pModel->HasTangentsAndBitangents())
			{
				tangent.x = pModel->mTangents[i].x;
				tangent.y = pModel->mTangents[i].y;
				tangent.z = pModel->mTangents[i].z;
				vertex.tangent = tangent;
			}
			else
			{
				vertex.tangent = glm::vec3(0.0f);
			}

			// Add the new vertex to the list of vertices ------------------------------
			vertices.push_back(vertex);
		}

		// Process indices -------------------------------------------------------------

		for (unsigned int i = 0; i < pModel->mNumFaces; i++)
		{
			aiFace face = pModel->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Add a new mesh
		m_pMeshList.push_back(new Mesh(&vertices[0], vertices.size(), &indices[0], indices.size()));
	}

	// ----------------------------------------------------------------------------

	void Object::RecursiveProcess(aiNode* pNode, const aiScene* pScene)
	{
		// Process
		for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
		{
			aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
			ProcessMesh(mesh);
		}

		// Recursion
		for (unsigned int i = 0; i < pNode->mNumChildren; i++)
		{
			RecursiveProcess(pNode->mChildren[i], pScene);
		}
	}
}

// ----------------------------------------------------------------------------