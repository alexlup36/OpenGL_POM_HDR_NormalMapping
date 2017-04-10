#ifndef __COMMON_H__
#define __COMMON_H__

#define GLM_FORCE_RADIANS 1
#define X_FULLSCREEN 0

// Define resolutions for window and full screen modes
#if X_FULLSCREEN
	#define WINDOW_WIDTH 1920
	#define WINDOW_HEIGHT 1080
#else
	#define WINDOW_WIDTH 1600
	#define WINDOW_HEIGHT 900
#endif // FULL_SCREEN

// Includes ------------------------------------------------------------------------------

#include <GL/glew.h>
#include <glfw3.h>

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>


// ---------------------------------------------------------------------------------------

void Log( const char* szMessage );
void Log( const char* szTag, const char* szMessage );
void GLClearErrors();
void GLErrorCheck( const char* szMessage = nullptr);

#endif // __COMMON_H__