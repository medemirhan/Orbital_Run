#include "CControllerConfigMenu.h"

CControllerConfigMenu::CControllerConfigMenu()
{

}

CControllerConfigMenu::~CControllerConfigMenu()
{

}

INT32S CControllerConfigMenu::InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model)
{
	model.GameState = STATES_CONFIG_MENU;
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
	}
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			return 0;
		case sf::Keyboard::Up:
			if (view.CurrentSelection > 0 && !view.WaitingEntry) {
				view.CurrentSelection--;
			}
			break;
		case sf::Keyboard::Down:
			if (view.CurrentSelection < 5 && !view.WaitingEntry) {
				view.CurrentSelection++;
			}
			break;
		case sf::Keyboard::Return:
			if (view.CurrentSelection == 4 && !view.WaitingEntry) {
				config_data.SetNumOrbits(model.NumOrbits);
				config_data.SetNumMonsters(model.NumMonsters);
				config_data.SetVOrbitron(model.VOrbitron);
				config_data.SetVMonster(model.VMonster);
				return 2;
			}
			else if (view.CurrentSelection == 5 && !view.WaitingEntry) {
				return 0;
			}
			else {
				view.WaitingEntry = !view.WaitingEntry;
				view.PlayerInput = "";
			}
			break;
		default:
			break;
		}
	}
	if (event.type == sf::Event::TextEntered && view.WaitingEntry) {
		if ((event.text.unicode > 47 && event.text.unicode < 58) || event.text.unicode == 46) {
			view.PlayerInput += event.text.unicode;
			switch (view.CurrentSelection) {
			case 0:
				view.TxtNumOrbits.setString(view.PlayerInput);
				model.NumOrbits = std::stof(std::string(view.PlayerInput));
				if (model.NumOrbits < LOWER_LIMIT_ORBIT_NUM || model.NumOrbits > UPPER_LIMIT_ORBIT_NUM) {
					model.NumOrbits = config_data.OrbitNumber;
				}
				break;
			case 1:
				view.TxtNumMonsters.setString(view.PlayerInput);
				model.NumMonsters = std::stof(std::string(view.PlayerInput));
				if (model.NumMonsters < LOWER_LIMIT_MONSTER_NUM || model.NumMonsters > UPPER_LIMIT_MONSTER_NUM) {
					model.NumMonsters = config_data.MonsterNumber;
				}
				break;
			case 2:
				view.TxtVOrbitron.setString(view.PlayerInput);
				model.VOrbitron = std::stof(std::string(view.PlayerInput));
				if (model.VOrbitron < LOWER_LIMIT_ORBITRON_VEL || model.VOrbitron > UPPER_LIMIT_ORBITRON_VEL) {
					model.VOrbitron = config_data.OrbitronVelocity;
				}
				break;
			case 3:
				view.TxtVMonster.setString(view.PlayerInput);
				model.VMonster = std::stof(std::string(view.PlayerInput));
				if (model.VMonster <LOWER_LIMIT_MONSTER_VEL || model.VMonster > UPPER_LIMIT_MONSTER_VEL) {
					model.VMonster = config_data.MonsterVelocity;
				}
				break;
			default:
				break;
			}
		}
	}
	return 1;
}