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
	CState* pCurrentState;
	BOOLEAN IsRunning;
	BOOLEAN FlagGameOver;
	BOOLEAN FlagLostLife;
	BOOLEAN FlagGamePaused;
public:
	CGame();
	~CGame();
	void OnStateHandler(sf::RenderWindow& window, CConfigurationData& config_data, CModel& model);
	static CState* pMainMenuState;          /* concrete state object */
	static CState* pConfigMenuState;        /* concrete state object */
	static CState* pPlayingState;           /* concrete state object */

	void SetIsRunning(BOOLEAN is_running);
	void SetState(CState* p_state);
	void SetFlagGameOver(BOOLEAN flag);
	void SetFlagLostLife(BOOLEAN flag);
	void SetFlagGamePaused(BOOLEAN flag);
	CState* GetState();
	BOOLEAN GetFlagGameOver();
	BOOLEAN GetFlagLostLife();
	BOOLEAN GetFlagGamePaused();
	BOOLEAN GetIsRunning();
};

