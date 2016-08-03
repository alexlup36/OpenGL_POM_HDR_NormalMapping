#ifndef __GFXSTATS_H__
#define __GFXSTATS_H__

#include "GameComponent.h"

class GfxStats : public GameComponent
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

	void Update(float dt);
	void Display(float dt);

private:
	float m_fFPS;
	float m_fMilisecondsPerFrame;

};

#endif // __GFXSTATS_H__