#pragma once
#include "CController.h"
#include "CConfigurationData.h"
#include "CViewMainMenu.h"

class CControllerMainMenu : public CController {
private:

public:
	CControllerMainMenu();
	~CControllerMainMenu();
	INT32S InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model);
	INT32S UserInputHandler(sf::Event& event, CViewMainMenu& view);
};

