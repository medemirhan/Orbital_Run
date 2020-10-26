#pragma once
#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"

class CTimer;
class CModel;
class CEntity;
class CViewMainMenu;
class CViewConfigMenu;
class CViewPlayingScreen;
class CGame;

class CController {
public:
	virtual INT32S StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) = 0;
};

