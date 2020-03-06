#ifndef __OBJECT_H__
#define __OBJECT_H__

// ----------------------------------------------------------------------------

#include <glm/mat4x4.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include "Common.h"

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "BaseTechnique.h"
#include "Material.h"

// ----------------------------------------------------------------------------
namespace GL
{
	class Object
	{
	private:

		// ----------------------------------------------------------------------------

		// Get the object mesh
		inline void renderMeshes()
		{
			// Render all meshes in the object
			for (std::vector<Mesh*>::iterator it = m_pMeshList.begin(); it != m_pMeshList.end(); it++)
			{
				(*it)->Render();
			};
		}

		// ----------------------------------------------------------------------------

		// Activate texture
		inline void bindTextures() const
		{
			if (m_pTexDiffuse != nullptr)
			{
				m_pTexDiffuse->Bind(0, m_pCurrentTechnique->getProgramID());
			}
			if (m_pTexDiffuse2 != nullptr)
			{
				m_pTexDiffuse2->Bind(1, m_pCurrentTechnique->getProgramID());
			}
			if (m_pTexNormal != nullptr)
			{
				m_pTexNormal->Bind(2, m_pCurrentTechnique->getProgramID());
			}
			if (m_pTexNormal2 != nullptr)
			{
				m_pTexNormal2->Bind(3, m_pCurrentTechnique->getProgramID());
			}
			if (m_pTexDisplacement != nullptr)
			{
				m_pTexDisplacement->Bind(4, m_pCurrentTechnique->getProgramID());
			}
			if (m_pTexSpecular != nullptr)
			{
				m_pTexSpecular->Bind(5, m_pCurrentTechnique->getProgramID());
			}
		}

		// ----------------------------------------------------------------------------

		// Activate pbr textures
		void bindPBRTextures() const
		{
			GLuint programID = m_pCurrentTechnique->getProgramID();

			if (m_pbrTexMaterial.albedoTexture != nullptr)
			{
				m_pbrTexMaterial.albedoTexture->Bind(0, programID);
			}
		}

		// ----------------------------------------------------------------------------

	public:
		// ----------------------------------------------------------------------------

		Object(const std::string& name,
			const std::string& modelPath,
			BaseTechnique* technique,
			Texture* diffuse = nullptr,
			Texture* diffuse2 = nullptr,
			Texture* normal = nullptr,
			Texture* normal2 = nullptr,
			Texture* displacement = nullptr,
			Texture* specular = nullptr);
		Object(const std::string& name,
			const std::string& modelPath,
			BaseTechnique* technique,
			Material* material);
		Object(const std::string& name,
			const std::string& modelPath,
			BaseTechnique* technique,
			Material* material,
			bool ui);
		Object(const std::string& name,
			const std::string& modelPath,
			BaseTechnique* technique,
			PBRMaterial* material);
		Object(const std::string& name,
			const std::string& modelPath,
			BaseTechnique* technique,
			PBRTexMaterial* material);
		~Object(void);

		void Init();

		// ----------------------------------------------------------------------------
		// Getters
		inline const glm::mat4 getModel() const { return m_pTransform->GetModel(); }
		inline const glm::vec3 getTranslation() const { return m_pTransform->GetPos(); }
		inline const glm::vec3 getRotation() const { return m_pTransform->GetRotation(); }
		inline const glm::vec3 Scale() const { return m_pTransform->GetScale(); }
		inline BaseTechnique* getTechnique() const { return m_pCurrentTechnique; }
		inline Material getMaterial() const { return m_pMaterial; }
		inline const std::string& getModelPath() const { return m_sModelPath; }
		inline const std::vector<Mesh*>& getMeshList() const { return m_pMeshList; }

		// ----------------------------------------------------------------------------
		// Setters
		inline void Translate(GLfloat x, GLfloat y, GLfloat z) { m_pTransform->SetPos(x, y, z); }
		inline void Rotate(GLfloat x, GLfloat y, GLfloat z) { m_pTransform->SetRotation(x, y, z); }
		inline void Scale(GLfloat x, GLfloat y, GLfloat z) { m_pTransform->SetScale(x, y, z); }
		inline void setTechnique(BaseTechnique* newTechnique) { m_pCurrentTechnique = newTechnique; }

		// Transform
		inline Transform* GetTransform() { return m_pTransform; }

		void update(float dt);
		void render();
		void setMaterial(Material* newMaterial);
		void setPBRMaterial(PBRMaterial* newMaterial);

		// Name of the object
		std::string Name;

	private:
		Object(Object&);

		bool m_bEnablePBR;
		bool m_bIsUI;

		// Path of the 3d model
		std::string m_sModelPath;

		// Transform 
		Transform* m_pTransform;

		// List of meshes which compose the object
		std::vector<Mesh*> m_pMeshList;

		// Technique
		BaseTechnique* m_pCurrentTechnique;

		// Textures
		Texture* m_pTexDiffuse;
		Texture* m_pTexDiffuse2;
		Texture* m_pTexSpecular;
		Texture* m_pTexNormal;
		Texture* m_pTexNormal2;
		Texture* m_pTexDisplacement;

		Material m_pMaterial;
		PBRMaterial m_pbrMaterial;
		PBRTexMaterial m_pbrTexMaterial;

		// Material shader uniform location
		struct MaterialUniformLocation
		{
			GLuint emissionCompLoc;
			GLuint ambientCompLoc;
			GLuint diffuseCompLoc;
			GLuint specularCompLoc;
			GLuint shinenessLoc;
		};

		// PBR material shader location
		struct PBRMaterialUniformLocation
		{
			GLuint albedoLoc;
			GLuint metallicLoc;
			GLuint roughnessLoc;
			GLuint aoLoc;
		};

		// Texture shader uniform location
		struct TextureUniformLocation
		{
			GLuint diffuseSampler0;
			GLuint diffuseSampler1;
			GLuint normalSampler0;
			GLuint normalSampler1;
			GLuint displacementSampler;
			GLuint specularSampler;
		};

		struct PBRTextureUniformLocation
		{
			GLuint albedoSampler;
			GLuint normalSampler;
			GLuint displacementSampler;
		};

		MaterialUniformLocation m_materialUniformLocation;
		PBRMaterialUniformLocation m_pbrMaterialUniformLocation;
		TextureUniformLocation m_textureUniformLocation;

		void setShaderMaterial();
		void setPBRShaderMaterial();

		// Object initialization
		void initMaterialUniformLocation();
		void initPBRMaterialUniformLocation();
		void initTextureUniformLocation();

		// Mesh processing
		void LoadMesh();
		void ProcessMesh(aiMesh* pModel);
		void RecursiveProcess(aiNode* pNode, const aiScene* pScene);
	};
}

#endif // __OBJECT_H__
