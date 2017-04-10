#include "GfxStats.h"
#include "TextMan.h"
#include "TechniqueMan.h"

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

void GfxStats::initialize()
{
	m_fTotalTime = 0.0f;

	m_fUIScale = 0.03f;
	m_fLeftPadding = 0.6f;
	m_fTopPadding = 0.05f;
	m_fVerticalOffset = 0.005f;
	m_fBarInitialSize = 2.0f;
	m_fUIVerticalSize = 0.05f;

	// Create simple color technique
	m_pSimpleColorTechnique = new SimpleColorTechnique();
	if (m_pSimpleColorTechnique->init() == false)
	{
		std::cout << "Failed to init SimpleColorTechnique. \n";
		return;
	}
	else
	{
		// Add technique to the tech manager
		TechniqueMan::Instance().registerTechnique(m_pSimpleColorTechnique);
	}
}

void 
GfxStats::Update(float dt)
{
	// Make static so that their values persist accross function calls.
	static float numFrames   = 0.0f;
	static float timeElapsed = 0.0f;

	// Increment total time
	m_fTotalTime += dt;

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

	// Update stats
	GfxStats::Instance().startMeasurement("updateStats");
	unsigned int index = 0;
	for each (auto& stat in m_mapUIStats)
	{
		float currentOffset = 2.0f - m_fTopPadding - index * (m_fUIVerticalSize + m_fVerticalOffset);
		updateStat(stat.first, currentOffset);
		index++;
	}
	GfxStats::Instance().endMeasurement("updateStats");
}

void 
GfxStats::Display(float dt)
{
	printStat();
}

void GfxStats::addStat(const std::string & statName)
{
	if (m_mapUIStats.find(statName) == m_mapUIStats.end())
	{
		GL::Object* uiStatObject = new GL::Object(statName,
			".\\Assets\\quad.obj",
			m_pSimpleColorTechnique,
			&m_mat,
			true);

		uiStatObject->Rotate((float)M_PI_2, 0.0f, 0.0f);
		uiStatObject->Scale(0.1f, 0.0f, 0.01f);

		// Add UI object to the list of renderable objects
		ObjectMan::GetInstance().addObject(uiStatObject);

		// Add the measurement data
		MeasurementData measurementData;
		measurementData.m_fMS = 0.0f;
		measurementData.m_fStartMeasurement = 0.0f;
		measurementData.m_fEndMeasurement = 0.0f;
		measurementData.m_pUIObject = uiStatObject;
		m_mapUIStats[statName] = measurementData;
	}
}

void GfxStats::updateStat(const std::string& statName, float verticalOffset)
{
	// Update UI

	// Frame time bar
	GL::Object* statObj = ObjectMan::GetInstance().getObject(statName);
	if (statObj != nullptr)
	{
		if (statName == "frameTime")
		{
			// Special cases
			const glm::vec3& currentScale = statObj->Scale();
			float newScale = m_fUIScale * m_fMilisecondsPerFrame;
			//std::cout << "ms per frame: " << m_fMilisecondsPerFrame << "\n";
			float newOffset = m_fBarInitialSize * newScale * 0.5f;

			statObj->Scale(newScale, currentScale.y, currentScale.z);
			statObj->Translate(m_fLeftPadding + newOffset, verticalOffset, 0.0f);
		}
		else
		{
			// Generic UI stat
			float fTimeSpent = 0.0f;
			auto& stat = m_mapUIStats.find(statName);
			if (stat != m_mapUIStats.end())
			{
				fTimeSpent = stat->second.m_fMS;
			}

			const glm::vec3& currentScale = statObj->Scale();
			float newScale = m_fUIScale * fTimeSpent;
			//std::cout << "time spent obj renderer: " << fTimeSpent << "\n";
			float newOffset = m_fBarInitialSize * newScale * 0.5f;

			statObj->Scale(newScale, currentScale.y, currentScale.z);
			statObj->Translate(m_fLeftPadding + newOffset, verticalOffset, 0.0f);
		}
	}
}

void GfxStats::printStat()
{
	GfxStats::Instance().startMeasurement("textRender");

	char* message = new char[50];
	unsigned int index = 0;
	int top = 580;
	int size = 8;
	int distance = size * 2;
	int left = 5;
	int currentVerticalOffset;
	for each (auto& stat in m_mapUIStats)
	{
		const std::string& statName = stat.first;

		// Calculate vertical offset for printing the text
		currentVerticalOffset = top - index * distance;
		updateStat(stat.first, static_cast<float>(currentVerticalOffset));
		index++;

		// Setup text
		float timeSpent = 0.0f;
		auto& stat = m_mapUIStats.find(statName);
		if (stat != m_mapUIStats.end())
		{
			if (statName == "frameTime")
			{
				timeSpent = m_fMilisecondsPerFrame;
			}
			else
			{
				timeSpent = stat->second.m_fMS;
			}
		}
		sprintf_s(message, 50, "%s: %f", statName.c_str(), timeSpent);

		// Print text
		TextMan::Instance().PrintText(message, left, currentVerticalOffset, size);
	}

	GfxStats::Instance().endMeasurement("textRender");
}

void GfxStats::startMeasurement(const std::string& statName)
{
	auto& stat = m_mapUIStats.find(statName);
	if (stat != m_mapUIStats.end())
	{
		(*stat).second.m_fStartMeasurement = (static_cast<float>(glfwGetTime()) * 1000.0f);
	}
}

void GfxStats::endMeasurement(const std::string& statName)
{
	auto& stat = m_mapUIStats.find(statName);
	if (stat != m_mapUIStats.end())
	{
		MeasurementData& measurementData = (*stat).second;
		measurementData.m_fEndMeasurement = (static_cast<float>(glfwGetTime()) * 1000.0f);
		measurementData.m_fMS = measurementData.m_fEndMeasurement - measurementData.m_fStartMeasurement;
	}
}