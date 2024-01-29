#ifndef __DEMO_PHYSIC_H__
#define __DEMO_PHYSIC_H__

#include "cocos2d.h"

USING_NS_CC;

class DemoPhysic : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(DemoPhysic);

private:
	void onMouseDown(EventMouse* event);

	Sprite* _character;
};

#endif // !__DEMO_PHYSIC_H__