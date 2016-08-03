#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Common.h"

#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "glm/mat4x4.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace Engine
{
	class Object
	{
	private:

		// Get the object mesh
		inline void RenderMeshes()
		{
			// Render all meshes in the object
			for (std::vector<Mesh*>::iterator it = m_pMeshList.begin(); it != m_pMeshList.end(); it++)
			{
				(*it)->Render();
			};
		}

		// Activate texture
		inline void BindTextures(const Engine::Shader* shader) const
		{
			if (m_pTexDiffuse != NULL)
			{
				m_pTexDiffuse->Bind(0, shader->ProgramID());
			}
			if (m_pTexNormal != NULL)
			{
				m_pTexNormal->Bind(1, shader->ProgramID());
			}
			if (m_pTexDisplacement != NULL)
			{
				m_pTexDisplacement->Bind(2, shader->ProgramID());
			}
			if (m_pTexSpecular != NULL)
			{
				m_pTexSpecular->Bind(3, shader->ProgramID());
			}
		}

	public:
		Object(const std::string& name, 
			const std::string& modelPath,
			Engine::Shader* shader,
			Engine::Texture* diffuse = NULL,
			Engine::Texture* normal = NULL,
			Engine::Texture* displacement = NULL,
			Engine::Texture* specular = NULL);
		~Object(void);

		// Get the model matrix
		const inline glm::mat4 GetModel() { return m_pTransform->GetModel(); }
		inline Engine::Shader* GetShader() { return m_pShader; }

		// Getters
		const glm::vec3 Translation() { return m_pTransform->GetPos(); }
		const glm::vec3 Rotation() { return m_pTransform->GetRotation(); }
		const glm::vec3 Scale() { return m_pTransform->GetScale(); }

		// Setters
		inline void Translate(GLfloat x, GLfloat y, GLfloat z) { m_pTransform->SetPos(x, y, z); }
		inline void Rotate(GLfloat x, GLfloat y, GLfloat z) { m_pTransform->SetRotation(x, y, z); }
		inline void Scale(GLfloat x, GLfloat y, GLfloat z) { m_pTransform->SetScale(x, y, z); }

		inline void AddChild(Object* child) { m_childrenList.push_back(child); }
		inline std::vector<Object*> GetChildren() { return m_childrenList; }
		inline void SetParent(Object* parent) {	m_pParentObject = parent; }

		// Transform
		inline Engine::Transform* GetTransform() { return m_pTransform; }

		// Render using the assigned shader
		void Render()
		{
			// Set the transform in the shader
			m_pShader->SetTransform(m_pTransform);
			// Pass the transform values as well as camera properties to the shader
			m_pShader->Update();
			// Bind the texture attached to the object
			BindTextures(m_pShader);
			// Go through the meshes and render them
			RenderMeshes();
		}

		void Render(Engine::Shader* shader)
		{
			shader->Enable();

			// Set the transform in the shader
			shader->SetTransform(m_pTransform);
			// Pass the transform values as well as camera properties to the shader
			shader->Update();
			// Bind the texture attached to the object
			BindTextures(shader);
			// Go through the meshes and render them
			RenderMeshes();

			shader->Disable();
		}

		// Name of the object
		std::string Name;

	private:
		Object(Object&);

		// Path of the 3d model
		std::string m_sModelPath;

		// List of children
		std::vector<Object*> m_childrenList;
		// Parent reference
		Object* m_pParentObject;

		// Transform 
		Engine::Transform* m_pTransform;

		// List of meshes which compose the object
		std::vector<Mesh*> m_pMeshList;

		// Shader
		Engine::Shader* m_pShader;

		// Textures
		Engine::Texture* m_pTexDiffuse;
		Engine::Texture* m_pTexSpecular;
		Engine::Texture* m_pTexNormal;
		Engine::Texture* m_pTexDisplacement;

		// Mesh processing
		void LoadMesh();
		void ProcessMesh(aiMesh* pModel);
		void RecursiveProcess(aiNode* pNode, const aiScene* pScene);
	};
}


#endif // __OBJECT_H__
