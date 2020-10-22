#include "CControllerMainMenu.h"

CControllerMainMenu::CControllerMainMenu()
{

}

CControllerMainMenu::~CControllerMainMenu()
{

}

INT32S CControllerMainMenu::InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model)
{
	model.SetGameState(STATES_MAIN_MENU);
	INT32S return_val = 1;
	//std::mutex mutex;
	CViewMainMenu view;
	app.setActive(true);
	view.SetSceneProperties();

	while (app.isOpen()) {
		sf::Event event;
		while (app.pollEvent(event)) {
			return_val = this->UserInputHandler(event, view);
			if (return_val != 0) {
				return return_val;
			}else {

			}
		}
		view.UpdateTextColors();
		
		view.PrintScreen(app);
		//app.setActive(false);
		//std::thread thread_print_screen(&CViewMainMenu::PrintScreen, std::ref(view), std::ref(app), std::ref(mutex));
		//thread_print_screen.join();
	}
	//return -1; ????????????
}

INT32S CControllerMainMenu::UserInputHandler(sf::Event& event, CViewMainMenu& view)
{
	if (event.type == sf::Event::Closed) {
		return -1;
	}else {

	}
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Up:
			if (view.GetCurrentSelection() > 0) {
				view.SetCurrentSelection(view.GetCurrentSelection() - 1);
			}else {

			}
			break;
		case sf::Keyboard::Down:
			if (view.GetCurrentSelection() < 2) {
				view.SetCurrentSelection(view.GetCurrentSelection() + 1);
			}else {

			}
			break;
		case sf::Keyboard::Return:
			if (view.GetCurrentSelection() == 0) {
				return 2;
			}else if (view.GetCurrentSelection() == 1) {
				return 1;
			}else {
				return -1;
			}
			break;
		default:
			break;
		}
	}else {

	}
	return 0;
}