#ifndef __GFXSTATS_H__
#define __GFXSTATS_H__

#include <map>

#include "Object.h"
#include "ObjectMan.h"
#include "SimpleColorTechnique.h"
#include "LightUtil.h"

class GfxStats
{
private:
	GfxStats(void);
	~GfxStats(void);

public:

	static GfxStats& Instance()
	{
		static GfxStats refInstance;

		return refInstance;
	}

	void initialize();
	void Update(float dt);
	void Display(float dt);

	void addStat(const std::string& statName);
	void updateStat(const std::string& statName, float verticalOffset);
	void printStat();
	
	void startMeasurement(const std::string& statName);
	void endMeasurement(const std::string& statName);

private:

	SimpleColorTechnique* m_pSimpleColorTechnique;

	// Frame total
	float m_fFPS;
	float m_fMilisecondsPerFrame;
	float m_fTotalTime;

	float m_fLeftPadding;
	float m_fTopPadding;
	float m_fVerticalOffset;
	float m_fUIVerticalSize;
	float m_fUIScale;
	float m_fBarInitialSize;

	Material m_mat;

	struct MeasurementData
	{
		float m_fMS;
		float m_fStartMeasurement;
		float m_fEndMeasurement;
		GL::Object* m_pUIObject;
	};

	std::map<std::string, MeasurementData> m_mapUIStats;

};

#endif // __GFXSTATS_H__