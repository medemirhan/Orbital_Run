#pragma once
#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CModel.h"
#include "type_definitions.h"

class CState;
class CStateMainMenu;
class CStateConfigMenu;
class CStatePlayingScreen;

class CGame {
private:
	CState* CurrentState;                    // current state (state variable)
	BOOLEAN IsRunning;
	BOOLEAN FlagGameOver;
	BOOLEAN FlagLostLife;
	BOOLEAN FlagGamePaused;
public:
	CGame();
	~CGame();
	void OnStateHandler(sf::RenderWindow& window, CConfigurationData& config_data, CModel& model);
	void SetIsRunning(BOOLEAN is_running);
	void SetState(CState* new_state);           // state setter function
	void SetFlagGameOver(BOOLEAN flag);
	void SetFlagLostLife(BOOLEAN flag);
	void SetFlagGamePaused(BOOLEAN flag);
	BOOLEAN GetFlagGameOver();
	BOOLEAN GetFlagLostLife();
	BOOLEAN GetFlagGamePaused();
	BOOLEAN GetIsRunning();
	CState* GetState();
	static CState* MainMenuState;          // concrete state objects
	static CState* ConfigMenuState;
	static CState* PlayingState;
};

