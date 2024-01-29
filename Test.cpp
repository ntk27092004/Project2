#include "Test.h"
#include "ui/CocosGUI.h"
#include "json/rapidjson.h"
#include "json/document.h"

bool Test::init()
{
	if (!Scene::init())
	{
		return false;
	}
	rapidjson::Document docs;

	std::string dataContent = cocos2d::FileUtils::getInstance()->getStringFromFile("Data-Entity/characterInit.json");
	docs.Parse(dataContent.c_str());
	auto thenames = docs["data"].GetArray();

	std::vector<std::string> names;
	for(int i = 0;i<thenames.Size();i++){
		names.push_back(thenames[i]["_character"].GetString());
	}

	for (int i = 0;i < names.size();i++) {
		log("%s", names[i].c_str());
	}
	float x = Director::getInstance()->getVisibleSize().width / 2;

	for (int i = 0; i < names.size(); i++)
	{
		auto button = ui::Button::create("CloseSelected.png");
		button->setTitleText(names[i]);
		button->setPositionX(x);
		button->setPositionY(100 + 50 * i);

		button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
			
			}
			});

		this->addChild(button, 1);

	}
	return true;
}

