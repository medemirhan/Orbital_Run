#include "CStateMainMenu.h"

CStateMainMenu::CStateMainMenu()
{

}

CStateMainMenu::~CStateMainMenu()
{

}

void CStateMainMenu::OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	INT32S state_return = pControllerMainMenu->StateHandler(game, window, config_data, model);
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

void CStateMainMenu::OnEntry(CGame& game)
{
	pControllerMainMenu = new CControllerMainMenu;
}

void CStateMainMenu::OnExit(CGame& game)
{
	delete pControllerMainMenu;
}