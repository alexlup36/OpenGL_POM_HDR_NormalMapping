#include "ObjectMan.h"

#include "TechniqueMan.h"
#include "GfxStats.h"

// ----------------------------------------------------------------------------

ObjectMan::ObjectMan()
{
	// Add UI stats
	//GfxStats::Instance().addStat("objectUpdate");
	//GfxStats::Instance().addStat("objectRender");
}

// ----------------------------------------------------------------------------

ObjectMan::~ObjectMan()
{
	std::list<BaseTechnique*> techList = TechniqueMan::Instance().getTechList();

	for (auto it = techList.begin(); it != techList.end(); ++it)
	{
		BaseTechnique* currentTech = *it;
		ObjectList objectList = getObjects(currentTech->getProgramID());

		TechniqueObjectMap::iterator first		= objectList.first;
		TechniqueObjectMap::iterator last		= objectList.second;

		for ( ; first != last; first++ )
		{
			if (first->second != nullptr)
			{
				delete first->second;
			}
		}
	}
}

// ----------------------------------------------------------------------------

// Render all the Meshes which have the specified shader attached
void ObjectMan::renderTech(const BaseTechnique* technique, float dt)
{
	// Perform the rendering step - render all the object which have associated the same technique
	ObjectList objList = getObjects(technique->getProgramID());

	// Enable technique
	technique->enable();

	TechniqueObjectMap::iterator first		= objList.first;
	TechniqueObjectMap::iterator last		= objList.second;

	for ( ; first != last; first++ )
	{
		// Get a reference to the current object
		GL::Object* currentObject = first->second;

		//if (currentObject->Name.find("pointLightPBRMesh") != std::string::npos ||
		//	currentObject->Name.find("pointLightPhongMesh") != std::string::npos ||
		//	currentObject->Name.find("quadObj") != std::string::npos)
		//{
		//	// Object is a light source mesh
		//	glDisable(GL_CULL_FACE);
		//	glEnable(GL_BLEND);
		//	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//	glBlendFunc(GL_DST_COLOR, GL_ZERO);
		//	glBlendEquation(GL_FUNC_ADD);
		//}
		//else
		//{
		//	glEnable(GL_CULL_FACE);
		//	glDisable(GL_BLEND);
		//}

		// Render using the associated technique
		currentObject->update(dt);
		currentObject->render();
	}
}

// ----------------------------------------------------------------------------

// Add an Mesh to the multimap
void ObjectMan::addObject(GL::Object* Object)
{
	m_mapTechniqueObject.insert(std::make_pair(Object->getTechnique()->getProgramID(), Object));

	m_mapObjects[Object->getModelPath()] = Object;
}

// ----------------------------------------------------------------------------

// Render a single object
void ObjectMan::renderObject(const std::string& sName, float dt)
{
	// Perform the rendering step - render the desired object
	TechniqueObjectMap::iterator start = m_mapTechniqueObject.begin();
	TechniqueObjectMap::iterator end = m_mapTechniqueObject.end();

	for (; start != end; start++)
	{
		GL::Object* currentObject = start->second;

		if (strcmp(sName.c_str(), currentObject->Name.c_str()) == 0)
		{
			currentObject->getTechnique()->enable();
			currentObject->update(dt);
			currentObject->render();
		}
	}
}

// ----------------------------------------------------------------------------

// Get an object
GL::Object* ObjectMan::getObject(const std::string& sName)
{
	// Perform the rendering step - render the desired object
	TechniqueObjectMap::iterator first = m_mapTechniqueObject.begin();
	TechniqueObjectMap::iterator last = m_mapTechniqueObject.end();

	for (; first != last; first++)
	{
		GL::Object* currentObject = first->second;

		if (strcmp(sName.c_str(), currentObject->Name.c_str()) == 0)
		{
			return currentObject;
		}
	}

	return nullptr;
}

// ----------------------------------------------------------------------------

GL::Object* ObjectMan::getObjectModel(const std::string& sModelPath)
{
	auto& it = m_mapObjects.find(sModelPath);
	if (it != m_mapObjects.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

// ----------------------------------------------------------------------------

// Get the list of meshes which have the same technique associated
ObjectList ObjectMan::getObjects(GLuint programID)
{
	return m_mapTechniqueObject.equal_range(programID);
}

// ----------------------------------------------------------------------------

void 
ObjectMan::renderAll(float dt)
{
	GfxStats::Instance().startMeasurement("objectRender");

	std::list<BaseTechnique*> techList = TechniqueMan::Instance().getTechList();

	for (auto it = techList.begin(); it != techList.end(); ++it)
	{
		renderTech(*it, dt);
	}

	GfxStats::Instance().endMeasurement("objectRender");
}

// ----------------------------------------------------------------------------