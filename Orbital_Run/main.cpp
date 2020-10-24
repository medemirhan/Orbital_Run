#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CGame.h"
#include "CModel.h"
#include "type_definitions.h"

INT32S main() {
	srand(time(nullptr));
	
	sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Orbital Run", sf::Style::Close);

	//std::string config_file = "config.xml";
	CGame game;
	CModel* p_model = nullptr;
	//game.MainMenuState = new CStateMainMenu;
	//game.ConfigMenuState = new CStateConfigMenu;
	//game.PlayingState = new CStatePlayingScreen;

	CConfigurationData config_data;
	if (config_data.GetConfigFileErrorStatus()) {
		return -1;
	}
	else {

	}

	while (game.GetIsRunning()) {
		p_model = new CModel(config_data);
		game.OnStateHandler(app, config_data, *p_model);
	}
	delete p_model;

	return 0;
}