#include "MappedProperties.h"

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Constructor/destructor

MappedProperties::MappedProperties()
{

}

MappedProperties::~MappedProperties()
{

}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Public methods

float MappedProperties::getFloatProperty(const std::string& propertyName)
{
	auto res = m_FloatProperties.find(propertyName);
	if (res != m_FloatProperties.end())
		return res->second;
	else
	{
		printf("Warning: Unable to find property: %s\n", propertyName.c_str());
		return 0.0f;
	}
}

// ----------------------------------------------------------------------------

bool MappedProperties::getBoolProperty(const std::string& propertyName)
{
	auto res = m_BoolProperties.find(propertyName);
	if (res != m_BoolProperties.end())
		return res->second;
	else
	{
		printf("Warning: Unable to find property: %s\n", propertyName.c_str());
		return false;
	}
}

// ----------------------------------------------------------------------------

void MappedProperties::watchDir(const char* configFile, LPTSTR lpDir)
{
	DWORD dwWaitStatus;
	HANDLE dwChangeHandle;
	TCHAR lpDrive[4];
	TCHAR lpFile[_MAX_FNAME];
	TCHAR lpExt[_MAX_EXT];

	_tsplitpath_s(lpDir, lpDrive, 4, NULL, 0, lpFile, _MAX_FNAME, lpExt, _MAX_EXT);

	dwChangeHandle = FindFirstChangeNotification(lpDir,
		FALSE,
		FILE_NOTIFY_CHANGE_LAST_ACCESS);
	if (dwChangeHandle == INVALID_HANDLE_VALUE)
	{
		printf("Error: FindFirstChangeNotification function failed.\n");
		BOOL res = FindCloseChangeNotification(dwChangeHandle);
		return;
	}

	// Wait for notifcation
	while (TRUE)
	{
		//printf("Waiting for notification. \n");
		dwWaitStatus = WaitForSingleObject(dwChangeHandle, INFINITE);

		switch (dwWaitStatus)
		{
		case WAIT_OBJECT_0:
		{
			//printf("File change notifcation. \n");

			// Parse file
			if (!parseFile(configFile))
			{
				printf("Failed to parse file \n");
				return;
			}

			// Wait for the next notification
			if (FindNextChangeNotification(dwChangeHandle) == FALSE)
			{
				printf("Error: FindNextChangeNotificaiton failed. \n");
				BOOL res = FindCloseChangeNotification(dwChangeHandle);
				return;
			}

			break;
		}
		case WAIT_TIMEOUT:
		{
			printf("No change in the timeout period. \n");
			BOOL res = FindCloseChangeNotification(dwChangeHandle);
			break;
		}
		default:
			printf("Unknown notification.\n");
			break;
		}

		// Test code
		//bool b1 = getBoolProperty("varName6_bool2");
		//float f = getFloatProperty("varName2");
		//printf("Read float value: %f; read bool value: %i \n", f, b1);
	}
}

// ----------------------------------------------------------------------------

void MappedProperties::initialize(const char* configFile)
{
	// Parse file
	if (!parseFile(configFile))
	{
		printf("Failed to parse file \n");
		return;
	}
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Private methods

bool MappedProperties::breakLine(const std::string& s, char delim, std::vector<std::string>& v)
{
	bool res = true;
	auto i = 0;
	auto pos = s.find(delim);
	// Handle delimiter not found
	while (pos != std::string::npos)
	{
		v.push_back(s.substr(i, pos - i));
		i = ++pos;
		pos = s.find(delim, pos);
		// Last token - end of the string
		if (pos == std::string::npos)
		{
			v.push_back(s.substr(i, s.length()));
		}
	}

	// We need to have 2 result tokens
	res = (v.size() == 2);
	return res;
}

// ----------------------------------------------------------------------------

void MappedProperties::removeSpaces(std::string& s)
{
	// Remove spaces
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
	// Remove tabs
	s.erase(std::remove(s.begin(), s.end(), '\t'), s.end());
}

// ----------------------------------------------------------------------------

bool MappedProperties::parseFile(const char* filePath)
{
	std::ifstream file;
	std::string line;
	file.open(filePath);

	// Cleanup dictionaries
	m_BoolProperties.clear();
	m_FloatProperties.clear();

	if (file.is_open())
	{
		// Read file
		while (getline(file, line))
		{
			// Break current line
			std::vector<std::string> tokens;
			removeSpaces(line);
			if (line == "")
				continue;
			else if (line[0] == '#')
				continue;
			else
			{
				if (breakLine(line, '=', tokens) == true)
				{
					// Convert result tokens to lower case

					// Check for bool values
					if (tokens[1] == "true" || tokens[1] == "false")
					{
						// Add result to dictionary
						m_BoolProperties[tokens[0]] = static_cast<bool>(tokens[1].c_str());
					}
					else
					{
						// Assume everything else is a float

						// Add result to dictionary
						m_FloatProperties[tokens[0]] = static_cast<float>(atof(tokens[1].c_str()));
					}
				}

				// Print results
				/*printf("\nLine breakdown: \n");
				for (size_t i = 0; i < tokens.size(); ++i)
				{
					printf("Element %i = %s \n", i, tokens[i].c_str());
				}*/
			}
		}

		return true;
	}
	else
	{
		printf("Failed to open file: %s \n", filePath);
		return false;
	}

	file.close();
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------