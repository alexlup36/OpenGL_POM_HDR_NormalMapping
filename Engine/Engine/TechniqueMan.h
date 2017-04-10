#ifndef TECHNIQUEMAN_H
#define TECHNIQUEMAN_H

// ----------------------------------------------------------------------------

#include "Common.h"
#include "BaseTechnique.h"

#include <vector>

// ----------------------------------------------------------------------------

class TechniqueMan
{
public:
	static TechniqueMan& Instance()
	{
		static TechniqueMan techniqueMan;
		return techniqueMan;
	}

	// Specific ------------------------------------------
	void registerTechnique(BaseTechnique* newTechnique);
	inline const std::list<BaseTechnique*>& getTechList() { return m_pTechList; }

	void update();

protected:
	TechniqueMan() {};											// Constructor
	TechniqueMan(TechniqueMan const&) = delete;					// Copy-constructor
	TechniqueMan& operator=(TechniqueMan const&) = delete;		// Assignment operator
	virtual ~TechniqueMan();

private:
	std::list<BaseTechnique*> m_pTechList;
};

// ----------------------------------------------------------------------------

#endif // TECHNIQUEMAN_H