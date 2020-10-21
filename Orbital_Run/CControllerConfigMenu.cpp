#include "CControllerConfigMenu.h"

CControllerConfigMenu::CControllerConfigMenu()
{

}

CControllerConfigMenu::~CControllerConfigMenu()
{

}

INT32S CControllerConfigMenu::InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model)
{
	model.SetGameState(STATES_CONFIG_MENU);
	INT32S return_val = 1;
	CViewConfigMenu view;
	view.SetSceneProperties();

	sf::Clock flash_display_clock;
	while (app.isOpen()) {
		sf::Event event;
		while (app.pollEvent(event)) {
			return_val = this->UserInputHandler(event, view, config_data, model);
			if (return_val != 1) {
				return return_val;
			}else {

			}
		}
		view.UpdateTextColors();
		view.PrintScreen(app, flash_display_clock);
	}
	return -1;
}

INT32S CControllerConfigMenu::UserInputHandler(sf::Event& event, CViewConfigMenu& view, CConfigurationData& config_data, CModel& model)
{
	if (event.type == sf::Event::Closed) {
		return -1;
	}else {

	}
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			return 0;
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
				return 2;
			}else if (view.GetCurrentSelection() == 5 && !view.GetWaitingEntry()) {
				return 0;
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
				model.SetNumOrbits(std::stof(std::string(view.GetPlayerInput())));
				if (model.GetNumOrbits() < LOWER_LIMIT_ORBIT_NUM || model.GetNumOrbits() > UPPER_LIMIT_ORBIT_NUM) {
					model.SetNumOrbits(config_data.GetOrbitNumber());
				}else {

				}
				break;
			case 1:
				view.TxtNumMonsters.setString(view.GetPlayerInput());
				model.SetNumMonsters(std::stof(std::string(view.GetPlayerInput())));
				if (model.GetNumMonsters() < LOWER_LIMIT_MONSTER_NUM || model.GetNumMonsters() > UPPER_LIMIT_MONSTER_NUM) {
					model.SetNumMonsters(config_data.GetMonsterNumber());
				}else {

				}
				break;
			case 2:
				view.TxtVOrbitron.setString(view.GetPlayerInput());
				model.SetVOrbitron(std::stof(std::string(view.GetPlayerInput())));
				if (model.GetVOrbitron() < LOWER_LIMIT_ORBITRON_VEL || model.GetVOrbitron() > UPPER_LIMIT_ORBITRON_VEL) {
					model.SetVOrbitron(config_data.GetOrbitronVelocity());
				}else {

				}
				break;
			case 3:
				view.TxtVMonster.setString(view.GetPlayerInput());
				model.SetVMonster(std::stof(std::string(view.GetPlayerInput())));
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
	return 1;
}