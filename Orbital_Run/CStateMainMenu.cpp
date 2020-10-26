#include "CStateMainMenu.h"

void CStateMainMenu::OnStateHandler(CGame* game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	INT32S state_return = p_controller_main_menu->StateHandler(game, window, config_data, model);
	switch (state_return) {
	case -1:
		game->SetIsRunning(false);
		break;
	case 0:
		game->SetState(CGame::MainMenuState);
		break;
	case 1:
		game->SetState(CGame::ConfigMenuState);
		break;
	case 2:
		game->SetState(CGame::PlayingState);
		break;
	default:
		break;
	}
}

void CStateMainMenu::OnEntry(CGame* game)
{
	p_controller_main_menu = new CControllerMainMenu;
}

void CStateMainMenu::OnExit(CGame* game)
{
	delete p_controller_main_menu;
}