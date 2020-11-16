#pragma once
#include "CController.h"
#include "CConfigurationData.h"
#include "CViewConfigMenu.h"

class CControllerConfigMenu : public CController {
private:

public:
	CControllerConfigMenu();
	~CControllerConfigMenu();
	INT32S StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	INT32S UserInputHandler(sf::Event& event, CViewConfigMenu& view, CConfigurationData& config_data, CModel& model);
};