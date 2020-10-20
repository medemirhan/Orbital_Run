#pragma once
#include <SFML/Graphics.hpp>
#include "CConfigurationData.h"

class CTimer;
class CModel;
class CEntity;
class CViewMainMenu;
class CViewConfigMenu;
class CViewPlayingScreen;

class CController {
public:
	virtual INT32S InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model) = 0;
};

