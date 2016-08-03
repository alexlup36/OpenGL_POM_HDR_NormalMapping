#ifndef __SHADERMAN_H__
#define __SHADERMAN_H__

#include "Common.h"
#include "GameComponent.h"
#include "Shader.h"

#include <list>


class GameComponent;


class ShaderMan : public GameComponent
{
private:
	// Typedefs
	typedef std::vector< Engine::Shader* >::iterator ShaderListIt;
	typedef std::vector< Engine::Shader* > ShaderList;

public:
	static ShaderMan& Instance()
	{
		static ShaderMan _shaderMan;
		return _shaderMan;
	}

	// Specific ------------------------------------------
	void AddShader( Engine::Shader* newShader );
	inline ShaderList GetShaderList() { return m_pShaderList; }

	// Override ------------------------------------------
	virtual void Update(float dt);

protected:
	ShaderMan() {}								// Constructor
	ShaderMan(ShaderMan const&);				// Copy-constructor
	ShaderMan& operator=(ShaderMan const&);		// Assignment operator
	virtual ~ShaderMan();

private:
	// ------------------------------------------------------
	ShaderList m_pShaderList;
};

#endif // __SHADERMAN_H__