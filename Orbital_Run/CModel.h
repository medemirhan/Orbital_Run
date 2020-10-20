#pragma once
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "CEntity.h"
#include "CConfigurationData.h"
#include "type_definitions.h"
#include "CTimer.h"

class CModel {
	friend class CController;
	friend class CControllerMainMenu;
	friend class CControllerConfigMenu;
	friend class CControllerPlayingScreen;
private:
	E_STATES GameState;
	FP32 GameLevel;
	INT32S NumOrbits;
	INT32S NumMonsters;
	FP32 VOrbitron;
	FP32 VMonster;
	std::vector<std::shared_ptr<CEntity>> EntityList;
	std::vector<std::shared_ptr<CEntity>> RocketsOnOrbits;
	std::vector<FP32> RocketFiringAngles;
	std::vector<std::shared_ptr<CEntity>> SleepingMonsters;
public:
	CModel();
	CModel(CConfigurationData& config_data);
	~CModel();
	void GenerateEntityOnRandomPoint(CConfigurationData& config_data, E_ENTITY_TYPES entity_type);
	/*UpdateEntityList ikiye ayrýlsýn UpdateEntityList ve UpdateEntityDrawings þeklinde*/
	/*UpdateEntityList model classýnda, UpdateEntityDrawings view classýnda iþlem yapsýn*/
	void UpdateEntityList(std::vector<std::shared_ptr<CEntity>>& p_entity_list, std::vector<sf::Sprite>& p_entity_drawings);
	std::vector<std::shared_ptr<CEntity>>& GetSleepingMonsters();
	std::vector<std::shared_ptr<CEntity>> GetEntityList();
	E_STATES GetGameState();
};