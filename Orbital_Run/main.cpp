#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"
#include "CGame.h"
#include "CModel.h"
#include "type_definitions.h"

#if TEST_MODE_ENABLED
FP32 angle_orbitron = 0;
FP32 angle_orbitron_prev_time = 0;
FP32 angle_monster = 0;
FP32 angle_monster_prev_time = 0;
FP32 angle_rocket = 0;
FP32 angle_rocket_prev_time = 0;
FP32 angle_littlelife = 0;
FP32 angle_littlelife_prev_time = 0;
FP32 angle_bomb = 0;
FP32 angle_bomb_prev_time = 0;
FP32 game_clck = 0;
FP32 game_clck_prev = 0;
FP32 vel_orbitron = 0;
FP32 vel_monster = 0;
FP32 vel_rocket = 0;
FP32 vel_littlelife = 0;
FP32 vel_bomb = 0;
#endif

INT32S main(int argc, char** argv)
{
	srand(time(nullptr));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Orbital Run", sf::Style::Close);

	CGame game;
	CConfigurationData* p_config_data = new CConfigurationData;
	if (p_config_data->GetConfigFileErrorStatus()) {
		return STATES_EXIT;
	}else {

	}

	while (game.GetIsRunning()) {
		CModel* p_model = new CModel(*p_config_data);
		game.OnStateHandler(window, *p_config_data, *p_model);
		delete p_model;
	}
	delete p_config_data;
	delete game.pMainMenuState;
	delete game.pConfigMenuState;
	delete game.pPlayingState;
	
	return 0;
}