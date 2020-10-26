#pragma once
#include "CState.h"
#include "CControllerMainMenu.h"

class CGame;

class CStateMainMenu : public CState {
private:
	CControllerMainMenu* p_controller_main_menu;
public:
	void OnStateHandler(CGame* game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	void OnEntry(CGame* game) override;
	void OnExit(CGame* game) override;
};

