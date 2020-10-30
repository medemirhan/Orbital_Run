#include "CStatePlayingScreen.h"

CStatePlayingScreen::CStatePlayingScreen()
{

}

CStatePlayingScreen::~CStatePlayingScreen()
{

}

/* Invokes Playing Screen State's StateHandler. Depending on the return of the StateHandler, assigns current state */
void CStatePlayingScreen::OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	INT32S state_return = pControllerPlayingScreen->StateHandler(game, window, config_data, model);
	switch (state_return) {
	case STATES_EXIT:
		game.SetIsRunning(false);
		break;
	case STATES_MAIN_MENU:
		game.SetState(CGame::pMainMenuState);
		break;
	case STATES_CONFIG_MENU:
		game.SetState(CGame::pConfigMenuState);
		break;
	case STATES_PLAYING_SCREEN:
		game.SetState(CGame::pPlayingState);
		break;
	default:
		break;
	}
}

/* Generates CControllerPlayingScreen object on the entry of this state, and initializes flags of game */
void CStatePlayingScreen::OnEntry(CGame& game)
{
	pControllerPlayingScreen = new CControllerPlayingScreen;
	game.SetFlagGameOver(false);
	game.SetFlagLostLife(false);
	game.SetFlagGamePaused(false);
}

/* Deallocates memory on the exit of this state */
void CStatePlayingScreen::OnExit()
{
	delete pControllerPlayingScreen;
}
