#ifndef __HORIZONTAL_LAYOUT_H__
#define __HORIZONTAL_LAYOUT_H__

#include "cocos2d.h"

USING_NS_CC;

class HorizontalLayout : public Node
{
public:
	bool init() override;

	CREATE_FUNC(HorizontalLayout);

	void alignment();
};


#endif // !__HORIZONTAL_LAYOUT_H__
