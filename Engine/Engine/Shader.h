#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Transform.h"

namespace Engine
{
	class Shader
	{
	public:
		Shader(const char* vertex_file_path = NULL, const char* fragment_file_path = NULL, Engine::Transform* pTransform = NULL);
		~Shader(void);

		void Update();

		// Enable the use of the shader
		void Enable() const;
		void Disable() const;

		// Get the uniform variable location
		GLuint GetUniformLocation(const char* uniformVarName);

		// Set the program ID
		void SetProgramID(GLuint newProgramID);
		// Return the program ID
		GLuint ProgramID() const;

		// Get/Set transformation
		Engine::Transform* GetTransform();
		void SetTransform(Engine::Transform* pTransform);

		bool operator<( const Shader& other) const;

	private:
		enum Uniforms
		{
			keMODELMATRIX,
			keVIEWMATRIX,
			kePROJECTIONMATRIX,
			keNORMALMATRIX,
			keEYEPOSW,

			keNUM_UNIFORMS,
		};

		// Vertex shader and fragment shader
		GLuint _VertexShaderID;
		GLuint _FragmentShaderID;

		// Shader program
		GLuint _ShaderProgramID;

		GLuint m_uiUniforms[ keNUM_UNIFORMS ];

		// File paths for both the vertex shader and fragment shader
		char _vertexShaderPath[100];
		char _fragmentShaderPath[100];

		// Transform reference
		Engine::Transform* m_pTransform;

		// Methods ----------------------------------------------------------------

		// Load vertex and fragment shader from file
		GLuint LoadShaders();

		// Read shader code from file to string
		int ReadShaderFromFile(std::string& shaderCode, const char* shaderPath);
		// Compile and check the shader
		void CompileShader(GLuint shaderID, std::string& shaderCode, const char* shaderPath);
		// Create the program
		void CreateProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
		
	};
}


#endif // __SHADER_H__