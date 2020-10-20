#pragma once
#include "CController.h"
#include "CConfigurationData.h"
#include "CViewConfigMenu.h"

class CControllerConfigMenu : public CController {
private:

public:
	CControllerConfigMenu();
	~CControllerConfigMenu();
	INT32S InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model);
	INT32S UserInputHandler(sf::Event& event, CViewConfigMenu& view, CConfigurationData& config_data, CModel& model);
};