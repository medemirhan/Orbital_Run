#include "CStatePlayingScreen.h"

void CStatePlayingScreen::OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	INT32S state_return = p_controller_playing_screen->StateHandler(game, window, config_data, model);
	switch (state_return) {
	case -1:
		game.SetIsRunning(false);
		break;
	case 0:
		game.SetState(CGame::MainMenuState);
		break;
	case 1:
		game.SetState(CGame::ConfigMenuState);
		break;
	case 2:
		game.SetState(CGame::PlayingState);
		break;
	default:
		break;
	}
}

void CStatePlayingScreen::OnEntry(CGame& game)
{
	p_controller_playing_screen = new CControllerPlayingScreen;
	game.SetFlagGameOver(false);
	game.SetFlagLostLife(false);
	game.SetFlagGamePaused(false);
}

void CStatePlayingScreen::OnExit(CGame& game)
{
	delete p_controller_playing_screen;
}
