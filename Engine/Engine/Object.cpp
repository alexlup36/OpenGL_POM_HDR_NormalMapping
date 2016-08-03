#include "Object.h"

namespace Engine
{
	Object::Object(const std::string& name, 
		const std::string& modelPath,
		Engine::Shader* shader,
		Engine::Texture* diffuseTex /*= NULL*/,
		Engine::Texture* normalTex /*= NULL*/,
		Engine::Texture* displacementTex /*= NULL*/,
		Engine::Texture* specular /*= NULL*/)
		: Name(name), 
		m_sModelPath(modelPath),
		m_childrenList(NULL),
		m_pParentObject(NULL),
		m_pShader(shader),
		m_pTexNormal(normalTex),
		m_pTexDiffuse(diffuseTex),
		m_pTexDisplacement(displacementTex),
		m_pTexSpecular(specular)
	{
		LoadMesh();

		m_pTransform = new Engine::Transform();
		m_pShader->SetTransform(m_pTransform);
	}

	Object::~Object(void)
	{
		// Delete the transform object
		if (m_pTransform != NULL)
		{
			delete m_pTransform;
			m_pTransform = NULL;
		}

		// Delete textures
		if (m_pTexDiffuse != NULL)
		{
			delete m_pTexDiffuse;
			m_pTexDiffuse = NULL;
		}
		if (m_pTexNormal != NULL)
		{
			delete m_pTexNormal;
			m_pTexNormal = NULL;
		}
		if (m_pTexDisplacement != NULL)
		{
			delete m_pTexDisplacement;
			m_pTexDisplacement = NULL;
		}

		// Delete the list of meshes attached to this object
		while (!m_pMeshList.empty())
		{
			delete m_pMeshList.back();
			m_pMeshList.pop_back();
		}

		// Delete the elements from the child list
		while (!m_childrenList.empty())
		{
			delete m_childrenList.back();
			m_childrenList.pop_back();
		}
	}

	// Mesh processing
	void 
	Object::LoadMesh()
	{
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
	
	void 
	Object::ProcessMesh(aiMesh* pModel)
	{
		std::vector<Vertex> vertices;
		std::vector<GLushort> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for( unsigned int i = 0; i < pModel->mNumVertices; i++ ) 
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

		for(unsigned int i = 0; i < pModel->mNumFaces; i++)
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

	void 
	Object::RecursiveProcess(aiNode* pNode, const aiScene* pScene)
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
