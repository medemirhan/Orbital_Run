#pragma once
#include "CController.h"
#include "CConfigurationData.h"
#include "CViewConfigMenu.h"

class CControllerConfigMenu : public CController {
private:
	CViewConfigMenu View;
public:
	CControllerConfigMenu();
	~CControllerConfigMenu();
	INT32S StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	INT32S UserInputHandler(sf::Event& event, CConfigurationData& config_data, CModel& model);
};