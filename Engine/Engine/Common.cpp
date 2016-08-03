#include "Common.h"

void Log( const char* szMessage )
{
#if DEBUG 
	std::cout << szMessage << std::endl;
#endif
}

void Log( const char* szTag, const char* szMessage )
{
#if DEBUG 
	std::cout << szTag << " : " << szMessage << std::endl;
#endif
}

void GLErrorCheck(const char* szMessage /*=NULL*/)
{
#if DEBUG
	GLenum checkResult = glGetError();

	if (checkResult != GL_NO_ERROR)
	{
		if (szMessage != NULL)
		{
			std::cout << szMessage << " - ";
		}
		
		switch ( checkResult )
		{
		case GL_NO_ERROR:
			break;
		case GL_INVALID_ENUM:
			std::cout << "ERROR: Invalid enum." << std::endl;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "ERROR: Invalid framebuffer operation." << std::endl;
			break;
		case GL_INVALID_INDEX:
			std::cout << "ERROR: Invalid index." << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cout << "ERROR: Invalid operation." << std::endl;
			break;
		case GL_INVALID_VALUE:
			std::cout << "ERROR: Invalid value." << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "ERROR: Out of memory." << std::endl;
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "ERROR: Stack overflow." << std::endl;
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "ERROR: Stack underflow." << std::endl;
			break;
		default:
			break;
		}

		
	}
#endif
}

void GLClearErrors()
{
#if DEBUG 
	glGetError();
#endif
}