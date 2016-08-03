#ifndef __MAPPEDPROPERTIES_H__
#define __MAPPEDPROPERTIES_H__

#include <map>
#include <string>
#include "Texture.h"
#include <glm/vec3.hpp>

class MappedProperties
{
public:
	MappedProperties(void) {}
	virtual ~MappedProperties(void)
	{
		// Delete the elements in the vector3 map
		std::map< std::string, glm::vec3* >::iterator vectorIter;
		for ( vectorIter = m_vector3Map.begin(); vectorIter != m_vector3Map.end(); vectorIter++ )
		{
			if ( vectorIter->second )
				delete vectorIter->second;
		}

		// Delete the elements in the texture map
		std::map< std::string, Engine::Texture* >::iterator textureIt;
		for ( textureIt = m_textureMap.begin(); textureIt != m_textureMap.end(); textureIt++ )
		{
			if ( textureIt->second )
				delete textureIt->second;
		}
	}

	// Add mapped values
	inline void AddFloat( const std::string& name, float value )
	{
		m_floatMap.insert( std::pair<std::string, float>(name, value) );
	}

	inline void AddVector3( const std::string& name, glm::vec3* value )
	{
		m_vector3Map.insert( std::pair<std::string, glm::vec3*>(name, value) );
	}

	inline void AddTexture( const std::string& name, Engine::Texture* value )
	{
		m_textureMap.insert( std::pair<std::string, Engine::Texture*>(name, value) );
	}

	// Retrieve mapped values
	inline float GetFloat( const std::string& name )
	{
		std::map< std::string, float >::iterator it = m_floatMap.find(name);
		return ( it != m_floatMap.end() ) ? it->second : 0;
	}

	inline glm::vec3* GetVector3( const std::string& name )
	{
		std::map< std::string, glm::vec3* >::iterator it = m_vector3Map.find(name);
		return ( it != m_vector3Map.end() ) ? it->second : NULL;
	}

	inline Engine::Texture*	GetTexture( const std::string& name )
	{
		std::map< std::string, Engine::Texture* >::iterator it = m_textureMap.find(name);
		return ( it != m_textureMap.end() ) ? it->second : NULL;
	}

	// Set mapped properties
	inline void SetFloat( const std::string& name, float newValue )
	{
		std::map< std::string, float >::iterator it = m_floatMap.find(name);
		if ( it != m_floatMap.end() )
		{
			it->second = newValue;
		}
	}

	inline void SetVector3( const std::string& name, glm::vec3* newValue )
	{
		std::map< std::string, glm::vec3* >::iterator it = m_vector3Map.find(name);
		if ( it != m_vector3Map.end() )
		{
			it->second = newValue;
		}
	}

	inline void SetTexture( const std::string& name, Engine::Texture* newValue )
	{
		std::map< std::string, Engine::Texture* >::iterator it = m_textureMap.find(name);
		if ( it != m_textureMap.end() )
		{
			it->second = newValue;
		}
	}

private:
	// Map string to float
	std::map< std::string, float >					m_floatMap;

	// Map string to vector3
	std::map< std::string, glm::vec3* >				m_vector3Map;

	// Map string to texture
	std::map< std::string, Engine::Texture* >		m_textureMap;

};

#endif // __MAPPEDPROPERTIES_H__

