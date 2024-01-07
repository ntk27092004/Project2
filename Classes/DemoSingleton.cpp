#include "DemoSingleton.h"

DemoSingleton* DemoSingleton::_instance;

DemoSingleton* DemoSingleton::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new DemoSingleton();
        _instance->init();
    }

    return _instance;
}

bool DemoSingleton::init()
{
    if (!Sprite::init())
    {
        log("Init DemoSingleton failed");
        return false;
    }

    _character = Sprite::create("HelloWorld.png");

    this->addChild(_character);
    return true;
}
