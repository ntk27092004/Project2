#ifndef __TEST_H__
#define __TEST_H__

#include "cocos2d.h"
#include "HorizontalLayout.h"

USING_NS_CC;

class Test : public Sprite
{
public:
	bool init() override;
	//int count = 0;
	CREATE_FUNC(Test);

};

#endif // !__TEST_H__
