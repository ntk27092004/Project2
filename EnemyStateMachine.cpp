//#include "EnemyStateMachine.h"
//
//EnemyStateMachine* EnemyStateMachine::create(Entity* entity)
//{
//    auto newObject = new EnemyStateMachine();
//    if (newObject != nullptr && newObject->init(entity))
//    {
//        newObject->autorelease();
//        return newObject;
//    }
//
//    CC_SAFE_DELETE(newObject);
//    return nullptr;
//}
//
//bool EnemyStateMachine::init(Entity* entity)
//{
//    if (!Node::init())
//    {
//        log("Init EnemyStateMachine failed!");
//        return false;
//    }
//
//    this->_entityTarget = entity;
//    this->scheduleUpdate();
//    return true;
//}
//
//void EnemyStateMachine::addState(std::string stateName, State* state)
//{
//    if (_states.find(stateName) != _states.end())
//    {
//        return;
//    }
//    _states.insert({ stateName, state });
//}
//
//void EnemyStateMachine::update(float dt)
//{
//    std::string updateState = _states[_currentState]->updateState();
//    if (updateState != _currentState)
//    {
//        _states[_currentState]->exitState();
//        _currentState = updateState;
//        _states[_currentState]->enterState(_entityTarget);
//    }
//}
//
//void EnemyStateMachine::onEnter()
//{
//    Node::onEnter();
//    _currentState = "patrol";
//    _states[_currentState]->enterState(_entityTarget);
//}
