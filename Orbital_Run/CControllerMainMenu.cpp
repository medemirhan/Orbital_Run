#include "CControllerMainMenu.h"

CControllerMainMenu::CControllerMainMenu()
{

}

CControllerMainMenu::~CControllerMainMenu()
{

}

/* Controls the current state operations. Invokes UserInputHandler if a key pressed. Invokes CView to update view if needed. */
/* Returns an integer that indicates enum of State which will be assigned as current state. */
INT32S CControllerMainMenu::StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	//game.SetState(CGame::pMainMenuState);
	INT32S return_val = 1;
	//std::mutex mutex;
	CViewMainMenu view;
	window.setActive(true);
	view.SetSceneProperties();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			return_val = this->UserInputHandler(event, view);
			if (return_val != STATES_MAIN_MENU) { /* If return differs from main menu, change the State */
				return return_val;
			}else {

			}
		}
		view.UpdateTextColors();
		
		view.PrintScreen(window); /* Invoke View to print current scene */
		//window.setActive(false);
		//std::thread thread_print_screen(&CViewMainMenu::PrintScreen, std::ref(view), std::ref(window), std::ref(mutex));
		//thread_print_screen.join();
	}
	return STATES_EXIT; /* If the while loop above exits, this means that window is closed. */
}

/* Takes Event as argument and performs necessary actions depending on the user button press */
INT32S CControllerMainMenu::UserInputHandler(sf::Event& event, CViewMainMenu& view)
{
	if (event.type == sf::Event::Closed) {
		return STATES_EXIT;
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
				return STATES_PLAYING_SCREEN;
			}else if (view.GetCurrentSelection() == 1) {
				return STATES_CONFIG_MENU;
			}else {
				return STATES_EXIT;
			}
			break;
		default:
			break;
		}
	}else {

	}
	
	return STATES_MAIN_MENU; /* If above If statements don't change the state, return current state */
}