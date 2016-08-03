#include "ObjectMan.h"

#include "ShaderMan.h"

ObjectMan::~ObjectMan()
{
	std::vector<Engine::Shader*> shaderList = ShaderMan::Instance().GetShaderList();

	for (size_t i = 0; i < shaderList.size(); i++)
	{
		ObjectList objectList = GetObjects(shaderList[i]->ProgramID());

		ShaderObjectMap::iterator first		= objectList.first;
		ShaderObjectMap::iterator last		= objectList.second;

		for ( ; first != last; first++ )
		{
			delete first->second;
		}
	}
}

// Render all the Meshes which have the specified shader attached
void ObjectMan::Display(const Engine::Shader* shaderObject)
{
	assert(shaderObject != NULL);
	
	// Enable the shader
	shaderObject->Enable();
	
	// Perform the rendering step - render all the object which have associated the same shader
	ObjectList objList = GetObjects(shaderObject->ProgramID());

	ShaderObjectMap::iterator first		= objList.first;
	ShaderObjectMap::iterator last		= objList.second;

	for ( ; first != last; first++ )
	{
		Engine::Object* currentObject = first->second;

		// Render using the default shader
		currentObject->Render();
	}

	// Disable the shader
	shaderObject->Disable();
}

// Add an Mesh to the multimap
void ObjectMan::AddObject(Engine::Object* Object)
{
	m_mapShaderObject.insert(std::make_pair(Object->GetShader()->ProgramID(), Object));
}

// Render a single object
void ObjectMan::RenderObject(const std::string& sName)
{
	// Perform the rendering step - render the desired object
	std::multimap <GLuint, Engine::Object*>::iterator first = m_mapShaderObject.begin();
	std::multimap <GLuint, Engine::Object*>::iterator last = m_mapShaderObject.end();

	for (; first != last; first++)
	{
		Engine::Object* currentObject = first->second;

		if (strcmp(sName.c_str(), currentObject->Name.c_str()) == 0)
		{
			Engine::Shader* tempShader = currentObject->GetShader();

			assert(tempShader != NULL);

			// Enable the shader
			tempShader->Enable();

			// Render using the default shader
			currentObject->Render();

			// Disable the shader
			tempShader->Disable();
		}
	}
}

// Get an object
Engine::Object* ObjectMan::GetObject(const std::string& sName)
{
	// Perform the rendering step - render the desired object
	std::multimap <GLuint, Engine::Object*>::iterator first = m_mapShaderObject.begin();
	std::multimap <GLuint, Engine::Object*>::iterator last = m_mapShaderObject.end();

	for (; first != last; first++)
	{
		Engine::Object* currentObject = first->second;

		if (strcmp(sName.c_str(), currentObject->Name.c_str()) == 0)
		{
			return currentObject;
		}
	}

	return nullptr;
}

// Get the list of Meshes which have the same shader associated
ObjectList ObjectMan::GetObjects(GLuint programID)
{
	return m_mapShaderObject.equal_range(programID);
}

void 
ObjectMan::Render(float dt)
{
	std::vector<Engine::Shader*> shaderList = ShaderMan::Instance().GetShaderList();

	for (size_t i = 0; i < shaderList.size(); i++)
	{
		Display(shaderList[i]);
	}
}