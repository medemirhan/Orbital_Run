#include "CStateConfigMenu.h"

CStateConfigMenu::CStateConfigMenu()
{

}

CStateConfigMenu::~CStateConfigMenu()
{

}

/* Invokes Config Menu State's StateHandler. Depending on the return of the StateHandler, assigns current state */
void CStateConfigMenu::OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	INT32S state_return = this->pController->StateHandler(game, window, config_data, model);
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

/* Generates CControllerConfigMenu object on the entry of this state */
void CStateConfigMenu::OnEntry(CGame& game)
{
	this->pController = DBG_NEW CControllerConfigMenu;
}

/* Deallocates memory on the exit of this state */
void CStateConfigMenu::OnExit()
{
	delete this->pController;
}