#pragma once
#include "CState.h"
#include "CControllerConfigMenu.h"

class CGame;

class CStateConfigMenu : public CState {
private:
	CControllerConfigMenu* pController;
public:
	CStateConfigMenu();
	~CStateConfigMenu();
	void OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	void OnEntry(CGame& game) override;
	void OnExit() override;
};
