#ifndef __OBJECTMAN_H__
#define __OBJECTMAN_H__

#include <map>

#include "Shader.h"
#include "Object.h"

#include "GameComponent.h"


// Types ----------------------------------------------------------------------------------
typedef std::multimap<GLuint, Engine::Object*>			ShaderObjectMap;
typedef std::pair<ShaderObjectMap::iterator, ShaderObjectMap::iterator>		ObjectList;

// ----------------------------------------------------------------------------------------------
class ObjectMan : public GameComponent
{
public:
	~ObjectMan();

	static ObjectMan& GetInstance()
	{
		static ObjectMan instance;
		return instance;
	}

	// Specific methods --------------------------------------
	void AddObject(Engine::Object*);
	void RenderObject(const std::string& sName);
	Engine::Object* GetObject(const std::string& sName);

	// Override ----------------------------------------------
	virtual void Render(float dt);

private:
	// Singleton class
	ObjectMan() {}
	ObjectMan(ObjectMan const&) = delete;              // Don't Implement.
	void operator=(ObjectMan const&) = delete;		  // Don't implement

	// Methods
	ObjectList GetObjects(GLuint programID);
	virtual void Display(const Engine::Shader* shaderObject);

	// Data
	std::multimap <GLuint, Engine::Object*> m_mapShaderObject;
};


#endif // __OBJECTMAN_H__