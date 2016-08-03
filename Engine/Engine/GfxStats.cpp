#include "GfxStats.h"
#include "TextMan.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <ostream>
#include <tchar.h>

GfxStats::GfxStats(void)
{
}


GfxStats::~GfxStats(void)
{
}

void 
GfxStats::Update(float dt)
{
	// Make static so that their values persist accross function calls.
	static float numFrames   = 0.0f;
	static float timeElapsed = 0.0f;

	// Increment the frame count.
	numFrames += 1.0f;

	// Accumulate how much time has passed.
	timeElapsed += dt;

	// Has one second passed?--we compute the frame statistics once 
	// per second.  Note that the time between frames can vary so 
	// these stats are averages over a second.
	if( timeElapsed >= 1.0f )
	{
		// Frames Per Second = numFrames / timeElapsed,
		// but timeElapsed approx. equals 1.0, so 
		// frames per second = numFrames.

		m_fFPS = numFrames;

		// Average time, in miliseconds, it took to render a single frame.
		m_fMilisecondsPerFrame = 1000.0f / m_fFPS;

		// Reset time counter and frame count to prepare for computing
		// the average stats over the next second.
		timeElapsed = 0.0f;
		numFrames   = 0.0f;
	}
}

void 
GfxStats::Display(float dt)
{
	char* message = new char[50];

	sprintf_s(message, 50, "Miliseconds per frame: %f", m_fMilisecondsPerFrame);
	TextMan::Instance().PrintText(message, 5, 15, 15);

	sprintf_s(message, 50, "Frames per second: %f", m_fFPS);
	TextMan::Instance().PrintText(message, 5, 30, 15);
}