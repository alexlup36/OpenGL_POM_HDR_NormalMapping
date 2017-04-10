#ifndef __OBJECTMAN_H__
#define __OBJECTMAN_H__

#include <map>
#include <string>

#include "BaseTechnique.h"
#include "Object.h"


// ----------------------------------------------------------------------------
// Types
typedef std::multimap<GLuint, GL::Object*> TechniqueObjectMap;
typedef std::pair<TechniqueObjectMap::iterator, TechniqueObjectMap::iterator> ObjectList;

// ----------------------------------------------------------------------------
class ObjectMan
{
public:
	~ObjectMan();

	static ObjectMan& GetInstance()
	{
		static ObjectMan instance;
		return instance;
	}

	// Specific methods --------------------------------------

	// Object management
	void addObject(GL::Object*);
	GL::Object* getObject(const std::string& sName);
	GL::Object* getObjectModel(const std::string& sModelPath);
	// Render methods
	void renderAll(float dt);
	void renderObject(const std::string& sName, float dt);
	// Getter method
	ObjectList getObjects(GLuint programID);

private:
	// Singleton class
	ObjectMan();
	ObjectMan(ObjectMan const&) = delete;              // Don't Implement.
	void operator=(ObjectMan const&) = delete;		  // Don't implement

	// Methods
	void renderTech(const BaseTechnique* technique, float dt);

	// Data
	TechniqueObjectMap m_mapTechniqueObject;
	std::map<std::string, GL::Object*> m_mapObjects;
};


#endif // __OBJECTMAN_H__