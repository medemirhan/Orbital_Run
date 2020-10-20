#include <iostream>
#include <SFML/Graphics.hpp>
//#include "CController.h"
#include "CViewHeaders.h"
#include "CControllerHeaders.h"
#include "CConfigurationData.h"
#include "type_definitions.h"

INT32S main()
{
	srand(time(nullptr));
	INT32S current_screen = 0;

	sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Orbital Run", sf::Style::Close);

	//std::string config_file = "config.xml";
	CConfigurationData config_data;
	if (config_data.GetConfigFileErrorStatus()) {
		return -1;
	}

	while (current_screen >= 0)
	{
		CModel* p_model = new CModel(config_data);
		E_STATES* p_game_state = new E_STATES;
		if (current_screen == 0) {
			CControllerMainMenu* p_controller_main_menu = new CControllerMainMenu;
			current_screen = p_controller_main_menu->InvokeScreen(app, config_data, *p_model);
			delete p_controller_main_menu;
		}
		else if (current_screen == 1) {
			CControllerConfigMenu* p_controller_config_menu = new CControllerConfigMenu;
			current_screen = p_controller_config_menu->InvokeScreen(app, config_data, *p_model);
			delete p_controller_config_menu;
		}
		else if (current_screen == 2) {
			CControllerPlayingScreen* p_controller_playing = new CControllerPlayingScreen;
			current_screen = p_controller_playing->InvokeScreen(app, config_data, *p_model);
			delete p_model, p_controller_playing;
		}
		else {
			app.close();
		}
	}
	return 0;
}