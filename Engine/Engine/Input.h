#ifndef __INPUT_H__
#define __INPUT_H__

#include "Common.h"

#define MOUSE_SPEED 0.3f

class Input
{
public:
	Input(void);
	~Input(void);

	// Update input
	static void Update(float dt, glm::vec3& newPosition, const glm::vec3& direction, const glm::vec3& right);

	// Mouse position
	static double X_MOUSEPOS;
	static double Y_MOUSEPOS;

	static double X_PREVIOUSPOS;
	static double Y_PREVIOUSPOS;
};

#endif // __INPUT_H__