#include "ShaderMan.h"

#include "Common.h"

void 
ShaderMan::AddShader( Engine::Shader* newShader )
{
	if ( newShader != NULL )
	{
		m_pShaderList.push_back( newShader );
	}
}

// Override 
ShaderMan::~ShaderMan(void) 
{
	//Engine::Log("ShaderMan cleaning.");

	for (ShaderListIt it = m_pShaderList.begin(); it != m_pShaderList.end(); it++)
	{
		delete *it;
	}

	//Engine::Log("ShaderMan cleaned.");
}

void 
ShaderMan::Update(float dt)
{
	for (ShaderListIt it = m_pShaderList.begin(); it != m_pShaderList.end(); it++)
	{
		(*it)->Update();
	}
}