#ifndef __GAMECOMPONENT_H__
#define __GAMECOMPONENT_H__


class GameComponent
{
protected:
	GameComponent(void) {}
	virtual ~GameComponent(void) {}

	virtual void Display(float dt) {}
	virtual void Update(float dt) {}
	virtual void Render(float dt) {}
};

#endif // __GAMECOMPONENT_H__