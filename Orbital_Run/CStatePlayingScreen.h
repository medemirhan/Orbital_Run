#pragma once
#include "CState.h"
#include "CControllerPlayingScreen.h"

class CGame;

class CStatePlayingScreen : public CState {
private:
	CControllerPlayingScreen* pControllerPlayingScreen;
public:
	CStatePlayingScreen();
	~CStatePlayingScreen();
	void OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	void OnEntry(CGame& game) override;
	void OnExit(CGame& game) override;
};

