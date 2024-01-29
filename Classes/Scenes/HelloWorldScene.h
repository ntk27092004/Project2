#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "Map/GameMap.h"
#include "Character/State/CharacterJumpState.h"
#include "KeyBoardInput.h"


USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    CharacterJumpState* _jump;
    virtual bool init();
    CREATE_FUNC(HelloWorld);
protected:
    KeyboardInput* _keyboard;
    Character* _character;
    float _moveSpeed;
    GameMap* _gameMap;

protected:
    void update(float dt) override;
    void onEnter() override;
    void onMouseDown(EventMouse* event);
};

#endif // __HELLOWORLD_SCENE_H__