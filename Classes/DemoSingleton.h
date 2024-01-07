#ifndef __DEMO_SINGLETON_H__
#define __DEMO_SINGLETON_H__

#include "cocos2d.h"

USING_NS_CC;

class DemoSingleton : public Sprite
{
public:
	static DemoSingleton* getInstance();
private:
	bool init() override;

private:
	static DemoSingleton* _instance;

	Sprite* _character;
};

#endif // !__DEMO_SINGLETON_H__
