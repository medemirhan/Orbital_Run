#include "CControllerConfigMenu.h"

CControllerConfigMenu::CControllerConfigMenu()
{
	pView = new CViewConfigMenu;
}

CControllerConfigMenu::~CControllerConfigMenu()
{
	delete pView;
}

/* Controls the current state operations. Invokes UserInputHandler if a key pressed. Invokes CView to update view if needed. */
/* Returns an integer that indicates enum of State which will be assigned as current state. */
INT32S CControllerConfigMenu::StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	//game.SetState(CGame::pConfigMenuState);
	INT32S return_val = 1;
	//std::mutex mutex;
	//CViewConfigMenu view;
	window.setActive(true);
	this->pView->SetSceneProperties();

	sf::Clock flash_display_clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			return_val = this->UserInputHandler(event, config_data, model);
			if (return_val != STATES_CONFIG_MENU) { /* If return differs from config menu, change the State */
				return return_val;
			}else {

			}
		}
		this->pView->UpdateTextColors();

		this->pView->PrintScreen(window, flash_display_clock); /* Invoke View to print current scene */

		//window.setActive(false);
		//std::thread thread_print_screen(&CViewConfigMenu::PrintScreen, std::ref(view), std::ref(window), std::ref(flash_display_clock), std::ref(mutex));
		//thread_print_screen.join();

	}
	return STATES_EXIT; /* If the while loop above exits, this means that window is closed. */
}

/* Takes Event as argument and performs necessary actions depending on the user button press */
INT32S CControllerConfigMenu::UserInputHandler(sf::Event& event, CConfigurationData& config_data, CModel& model)
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
			if (this->pView->GetCurrentSelection() > 0 && !this->pView->GetWaitingEntry()) {
				this->pView->SetCurrentSelection(this->pView->GetCurrentSelection() - 1);
			}else {

			}
			break;
		case sf::Keyboard::Down:
			if (this->pView->GetCurrentSelection() < 5 && !this->pView->GetWaitingEntry()) {
				this->pView->SetCurrentSelection(this->pView->GetCurrentSelection() + 1);
			}else {

			}
			break;
		case sf::Keyboard::Return:
			if (this->pView->GetCurrentSelection() == 4 && !this->pView->GetWaitingEntry()) {
				config_data.SetOrbitNumber(model.GetNumOrbits());
				config_data.SetMonsterNumber(model.GetNumMonsters());
				config_data.SetOrbitronVelocity(model.GetVOrbitron());
				config_data.SetMonsterVelocity(model.GetVMonster());
				return STATES_PLAYING_SCREEN;
			}else if (this->pView->GetCurrentSelection() == 5 && !this->pView->GetWaitingEntry()) {
				return STATES_MAIN_MENU;
			}else {
				this->pView->SetWaitingEntry(!this->pView->GetWaitingEntry());
				this->pView->SetPlayerInput("");
			}
			break;
		default:
			break;
		}
	}else {

	}
	if (event.type == sf::Event::TextEntered && this->pView->GetWaitingEntry()) {
		if ((event.text.unicode > 47 && event.text.unicode < 58) || event.text.unicode == 46) {
			this->pView->SetPlayerInput(this->pView->GetPlayerInput() + event.text.unicode);
			switch (this->pView->GetCurrentSelection()) {
			case 0:
				this->pView->TxtNumOrbits.setString(this->pView->GetPlayerInput());
				model.SetNumOrbits(std::stoi(std::string(this->pView->GetPlayerInput())));
				if (model.GetNumOrbits() < LOWER_LIMIT_ORBIT_NUM || model.GetNumOrbits() > UPPER_LIMIT_ORBIT_NUM) {
					model.SetNumOrbits(config_data.GetOrbitNumber());
				}else {

				}
				break;
			case 1:
				this->pView->TxtNumMonsters.setString(this->pView->GetPlayerInput());
				model.SetNumMonsters(std::stoi(std::string(this->pView->GetPlayerInput())));
				if (model.GetNumMonsters() < LOWER_LIMIT_MONSTER_NUM || model.GetNumMonsters() > UPPER_LIMIT_MONSTER_NUM) {
					model.SetNumMonsters(config_data.GetMonsterNumber());
				}else {

				}
				break;
			case 2:
				this->pView->TxtVOrbitron.setString(this->pView->GetPlayerInput());
				model.SetVOrbitron(std::stof(std::string(this->pView->GetPlayerInput())));
				if (model.GetVOrbitron() < LOWER_LIMIT_ORBITRON_VEL || model.GetVOrbitron() > UPPER_LIMIT_ORBITRON_VEL) {
					model.SetVOrbitron(config_data.GetOrbitronVelocity());
				}else {

				}
				break;
			case 3:
				this->pView->TxtVMonster.setString(this->pView->GetPlayerInput());
				model.SetVMonster(std::stof(std::string(this->pView->GetPlayerInput())));
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