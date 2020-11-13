#pragma once
#include "CController.h"
#include "CConfigurationData.h"
#include "CViewMainMenu.h"

class CControllerMainMenu : public CController {
private:
	CViewMainMenu* pView;
public:
	CControllerMainMenu();
	~CControllerMainMenu();
	INT32S StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	INT32S UserInputHandler(sf::Event& event);
};

