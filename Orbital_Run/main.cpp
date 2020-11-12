#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>

#include "type_definitions.h"
#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CGame.h"
#include "CModel.h"

INT32S main(int argc, char** argv) {
	
	srand(time(nullptr));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Orbital Run", sf::Style::Close);

	CGame game;
	CConfigurationData* p_config_data = DBG_NEW CConfigurationData;
	if (p_config_data->GetConfigFileErrorStatus()) {
		return STATES_EXIT;
	}else {

	}

	while (game.GetIsRunning()) {
		CModel* p_model = DBG_NEW CModel(*p_config_data);
		game.OnStateHandler(window, *p_config_data, *p_model);
		delete p_model;
	}
	delete p_config_data;
	delete game.pMainMenuState;
	delete game.pConfigMenuState;
	delete game.pPlayingState;
	
	_CrtDumpMemoryLeaks();
	return 0;
}