#include "CControllerMainMenu.h"

CControllerMainMenu::CControllerMainMenu()
{

}

CControllerMainMenu::~CControllerMainMenu()
{

}

INT32S CControllerMainMenu::InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model)
{
	model.GameState = STATES_MAIN_MENU;
	INT32S return_val = 1;
	CViewMainMenu view;
	view.SetSceneProperties();
	
	while (app.isOpen()) {
		sf::Event event;
		while (app.pollEvent(event)) {
			return_val = this->UserInputHandler(event, view);
			if (return_val != 0) {
				return return_val;
			}
		}
		view.UpdateTextColors();
		view.PrintScreen(app);
	}
	//return -1; ????????????
}

INT32S CControllerMainMenu::UserInputHandler(sf::Event& event, CViewMainMenu& view)
{
	if (event.type == sf::Event::Closed) {
		return -1;
	}
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Up:
			if (view.CurrentSelection > 0) {
				view.CurrentSelection--;
			}
			break;
		case sf::Keyboard::Down:
			if (view.CurrentSelection < 2) {
				view.CurrentSelection++;
			}
			break;
		case sf::Keyboard::Return:
			if (view.CurrentSelection == 0) {
				return 2;
			}
			else if (view.CurrentSelection == 1) {
				return 1;
			}
			else {
				return -1;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}