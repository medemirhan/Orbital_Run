#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CGame.h"
#include "CModel.h"
#include "type_definitions.h"

INT32S main(int argc, char** argv) {
	srand(time(nullptr));
	
	sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Orbital Run", sf::Style::Close);

	CGame game;
	CConfigurationData config_data;
	if (config_data.GetConfigFileErrorStatus()) {
		return -1;
	}else {

	}

	while (game.GetIsRunning()) {
		std::shared_ptr<CModel> p_model(new CModel(config_data));
		game.OnStateHandler(app, config_data, *p_model);
	}

	return 0;
}