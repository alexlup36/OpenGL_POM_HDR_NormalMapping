#ifndef __MAPPEDPROPERTIES_H__
#define __MAPPEDPROPERTIES_H__

// ----------------------------------------------------------------------------

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// ----------------------------------------------------------------------------

class MappedProperties
{
public:
	~MappedProperties();

	static MappedProperties& GetInstance()
	{
		static MappedProperties instance;
		return instance;
	}

	// Specific methods --------------------------------------
	float getFloatProperty(const std::string& propertyName);
	bool getBoolProperty(const std::string& propertyName);

	void watchDir(const char* configFile, LPTSTR lpDir);
	void initialize(const char* configFile);

private:
	// Singleton class
	MappedProperties();
	MappedProperties(MappedProperties const&) = delete;			// Don't Implement.
	void operator=(MappedProperties const&) = delete;			// Don't implement

	// Methods
	bool breakLine(const std::string& s, char delim, std::vector<std::string>& v);
	void removeSpaces(std::string& s);
	bool parseFile(const char* filePath);

private:
	// Members
	std::map<std::string, float> m_FloatProperties;
	std::map<std::string, bool> m_BoolProperties;

};

#endif // __MAPPEDPROPERTIES_H__

