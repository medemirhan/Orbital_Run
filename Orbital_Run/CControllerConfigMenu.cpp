#include "CControllerConfigMenu.h"

CControllerConfigMenu::CControllerConfigMenu()
{

}

CControllerConfigMenu::~CControllerConfigMenu()
{

}

/* Controls the current state operations. Invokes UserInputHandler if a key pressed. Invokes CView to update view if needed. */
/* Returns an integer that indicates enum of State which will be assigned as current state. */
INT32S CControllerConfigMenu::StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	//game.SetState(CGame::pConfigMenuState);
	INT32S return_val = 1;
	//std::mutex mutex;
	CViewConfigMenu view;
	window.setActive(true);
	view.SetSceneProperties();

	sf::Clock flash_display_clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			return_val = this->UserInputHandler(event, view, config_data, model);
			if (return_val != STATES_CONFIG_MENU) { /* If return differs from config menu, change the State */
				return return_val;
			}else {

			}
		}
		view.UpdateTextColors();

		view.PrintScreen(window, flash_display_clock); /* Invoke View to print current scene */

		//window.setActive(false);
		//std::thread thread_print_screen(&CViewConfigMenu::PrintScreen, std::ref(view), std::ref(window), std::ref(flash_display_clock), std::ref(mutex));
		//thread_print_screen.join();

	}
	return STATES_EXIT; /* If the while loop above exits, this means that window is closed. */
}

/* Takes Event as argument and performs necessary actions depending on the user button press */
INT32S CControllerConfigMenu::UserInputHandler(sf::Event& event, CViewConfigMenu& view, CConfigurationData& config_data, CModel& model)
{
	if (event.type == sf::Event::Closed) {
		return STATES_EXIT;
	}else {

	}
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			return STATES_MAIN_MENU;
		case sf::Keyboard::Up:
			if (view.GetCurrentSelection() > 0 && !view.GetWaitingEntry()) {
				view.SetCurrentSelection(view.GetCurrentSelection() - 1);
			}else {

			}
			break;
		case sf::Keyboard::Down:
			if (view.GetCurrentSelection() < 5 && !view.GetWaitingEntry()) {
				view.SetCurrentSelection(view.GetCurrentSelection() + 1);
			}else {

			}
			break;
		case sf::Keyboard::Return:
			if (view.GetCurrentSelection() == 4 && !view.GetWaitingEntry()) {
				config_data.SetOrbitNumber(model.GetNumOrbits());
				config_data.SetMonsterNumber(model.GetNumMonsters());
				config_data.SetOrbitronVelocity(model.GetVOrbitron());
				config_data.SetMonsterVelocity(model.GetVMonster());
				return STATES_PLAYING_SCREEN;
			}else if (view.GetCurrentSelection() == 5 && !view.GetWaitingEntry()) {
				return STATES_MAIN_MENU;
			}else {
				view.SetWaitingEntry(!view.GetWaitingEntry());
				view.SetPlayerInput("");
			}
			break;
		default:
			break;
		}
	}else {

	}
	if (event.type == sf::Event::TextEntered && view.GetWaitingEntry()) {
		if ((event.text.unicode > 47 && event.text.unicode < 58) || event.text.unicode == 46) {
			view.SetPlayerInput(view.GetPlayerInput() + event.text.unicode);
			switch (view.GetCurrentSelection()) {
			case 0:
				view.TxtNumOrbits.setString(view.GetPlayerInput());
				model.SetNumOrbits(std::stoi(std::string(view.GetPlayerInput())));
				if (model.GetNumOrbits() < LOWER_LIMIT_ORBIT_NUM || model.GetNumOrbits() > UPPER_LIMIT_ORBIT_NUM) {
					model.SetNumOrbits(config_data.GetOrbitNumber());
				}else {

				}
				break;
			case 1:
				view.TxtNumMonsters.setString(view.GetPlayerInput());
				model.SetNumMonsters(std::stoi(std::string(view.GetPlayerInput())));
				if (model.GetNumMonsters() < LOWER_LIMIT_MONSTER_NUM || model.GetNumMonsters() > UPPER_LIMIT_MONSTER_NUM) {
					model.SetNumMonsters(config_data.GetMonsterNumber());
				}else {

				}
				break;
			case 2:
				view.TxtVOrbitron.setString(view.GetPlayerInput());
				model.SetVOrbitron((std::stof(std::string(view.GetPlayerInput()))) * VELOCITY_TRANSFORM_COEFF);
				if (model.GetVOrbitron() < LOWER_LIMIT_ORBITRON_VEL || model.GetVOrbitron() > UPPER_LIMIT_ORBITRON_VEL) {
					model.SetVOrbitron(config_data.GetOrbitronVelocity());
				}else {

				}
				break;
			case 3:
				view.TxtVMonster.setString(view.GetPlayerInput());
				model.SetVMonster((std::stof(std::string(view.GetPlayerInput()))) * VELOCITY_TRANSFORM_COEFF);
				if (model.GetVMonster() <LOWER_LIMIT_MONSTER_VEL || model.GetVMonster() > UPPER_LIMIT_MONSTER_VEL) {
					model.SetVMonster(config_data.GetMonsterVelocity());
				}else {

				}
				break;
			default:
				break;
			}
		}else {

		}
	}else {

	}

	return STATES_CONFIG_MENU; /* If above If statements don't change the state, return current state */
}