#include "Test.h"
#include "ui/CocosGUI.h"

bool Test::init()
{
    if (!Sprite::init())
    {
        log("Init Test failed!");
        return false;
    }
    

    return true;
}
