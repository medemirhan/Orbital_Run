#pragma once
#include "CState.h"
#include "CControllerMainMenu.h"

class CGame;

class CStateMainMenu : public CState {
private:
	CControllerMainMenu* pControllerMainMenu;
public:
	CStateMainMenu();
	~CStateMainMenu();
	void OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	void OnEntry(CGame& game) override;
	void OnExit() override;
};

