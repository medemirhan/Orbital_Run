#include "CStateConfigMenu.h"

CStateConfigMenu::CStateConfigMenu()
{

}

CStateConfigMenu::~CStateConfigMenu()
{

}

void CStateConfigMenu::OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	INT32S state_return = pControllerConfigMenu->StateHandler(game, window, config_data, model);
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

void CStateConfigMenu::OnEntry(CGame& game)
{
	pControllerConfigMenu = new CControllerConfigMenu;
}

void CStateConfigMenu::OnExit(CGame& game)
{
	delete pControllerConfigMenu;
}