#pragma once
#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "CEntity.h"
#include "COrbitron.h"
#include "CMonster.h"
#include "CRocket.h"
#include "CRocketRight.h"
#include "CBomb.h"
#include "CLife.h"
#include "CView.h"
//#include "CController.h"
#include "CModel.h"
#include "CConfigurationData.h"
#include "CTimer.h"
//#include "type_definitions.h"

class CViewPlayingScreen : public CView {
	friend class CControllerPlayingScreen;
private:
	//std::vector<std::shared_ptr<CEntity>> EntityList;
	std::vector<sf::Sprite> EntityDrawings;
	std::vector<sf::Texture> EntityTextures;
	//std::vector<std::shared_ptr<CEntity>> RocketsOnOrbits;
	//std::vector<FP32> RocketFiringAngles;
	//std::vector<std::shared_ptr<CEntity>> SleepingMonsters;
	std::vector<sf::CircleShape> Orbits;
	sf::RectangleShape Mask;
	sf::Text TxtScore, TxtGameLevel, TxtLife, TxtLittlelife, TxtRocketRight, TxtLostLife, TxtLostLifeOptions, TxtGameOver, TxtGameOverOptions, TxtGamePaused, TxtGamePausedOptions;
	sf::Sprite BackgroundSprite, LevelIcon, LifeIcon, LittlelifeIcon, RocketRightIcon;
	sf::Font Font, TextFont, WarningFont;
	sf::Texture Texture, LevelIconTexture, LifeIconTexture, LittlelifeIconTexture, RocketRightIconTexture;
public:
	CViewPlayingScreen();
	~CViewPlayingScreen();
	void SetSceneProperties();
	//INT32S Run(sf::RenderWindow& app, CConfigurationData& config_data, E_STATES& game_state, CController& controller);
	void GenerateOrbitDrawings(const CConfigurationData& init_config_data);
	void GenerateEntityDrawings(const CConfigurationData& init_config_data, const std::shared_ptr<CEntity> p_entity);
	void PrintScreen(sf::RenderWindow& app, std::vector<std::shared_ptr<CEntity>>& p_entity_list, E_STATES& game_state, INT32S num_orbits);
	//std::vector<std::shared_ptr<CEntity>>& GetSleepingMonsters();
	void UpdateIndicatorsView(FP32 game_level, INT32S indicator_num_life, INT32S indicator_num_littlelife, INT32S indicator_num_rocketright);
};