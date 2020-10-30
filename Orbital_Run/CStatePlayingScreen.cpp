#include "CStatePlayingScreen.h"

CStatePlayingScreen::CStatePlayingScreen()
{

}

CStatePlayingScreen::~CStatePlayingScreen()
{

}

void CStatePlayingScreen::OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	INT32S state_return = pControllerPlayingScreen->StateHandler(game, window, config_data, model);
	switch (state_return) {
	case -1:
		game.SetIsRunning(false);
		break;
	case 0:
		game.SetState(CGame::pMainMenuState);
		break;
	case 1:
		game.SetState(CGame::pConfigMenuState);
		break;
	case 2:
		game.SetState(CGame::pPlayingState);
		break;
	default:
		break;
	}
}

void CStatePlayingScreen::OnEntry(CGame& game)
{
	pControllerPlayingScreen = new CControllerPlayingScreen;
	game.SetFlagGameOver(false);
	game.SetFlagLostLife(false);
	game.SetFlagGamePaused(false);
}

void CStatePlayingScreen::OnExit(CGame& game)
{
	delete pControllerPlayingScreen;
}
