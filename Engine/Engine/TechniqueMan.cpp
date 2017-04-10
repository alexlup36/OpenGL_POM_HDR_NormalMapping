#include "TechniqueMan.h"

#include "GfxStats.h"

// ----------------------------------------------------------------------------

TechniqueMan::~TechniqueMan()
{
	for (auto it = m_pTechList.begin(); it != m_pTechList.end(); it++)
	{
		BaseTechnique* currentTech = *it;
		if (currentTech != nullptr)
		{
			delete currentTech;
		}
	}
}

// ----------------------------------------------------------------------------

void TechniqueMan::registerTechnique(BaseTechnique* newTechnique)
{
	if (newTechnique != nullptr)
	{
		m_pTechList.push_back(newTechnique);
	}
}

// ----------------------------------------------------------------------------

void TechniqueMan::update()
{
	GfxStats::Instance().startMeasurement("updateTechnique");
	GLClearErrors();

	for (auto it = m_pTechList.begin(); it != m_pTechList.end(); it++)
	{
		BaseTechnique* currentTech = *it;
		currentTech->enable();
		currentTech->update();
	}

	GLErrorCheck("TechniqueMan::update");
	GfxStats::Instance().endMeasurement("updateTechnique");
}

// ----------------------------------------------------------------------------
