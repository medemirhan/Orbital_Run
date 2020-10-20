#pragma once
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "CEntity.h"
#include "CConfigurationData.h"
//#include "CViewPlayingScreen.h"
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
	//static std::vector<std::vector<std::shared_ptr<CEntity>>> CollisionDetection(const std::vector<std::shared_ptr<CEntity>>& p_entity_list);
	//static void CollisionHandler(CConfigurationData& config_data, std::vector<std::vector<std::shared_ptr<CEntity>>>& p_collision_list, std::vector<E_COLLISION_TYPES>* p_collision_types, E_STATES& game_state, std::vector<std::shared_ptr<CEntity>>& p_sleeping_monsters, const sf::Clock& global_clock, sf::Clock& interrupt_clock, CTimer& timer);
	/*UpdateEntityList ikiye ayrýlsýn UpdateEntityList ve UpdateEntityDrawings þeklinde*/
	/*UpdateEntityList model classýnda, UpdateEntityDrawings view classýnda iþlem yapsýn*/
	void UpdateEntityList(std::vector<std::shared_ptr<CEntity>>& p_entity_list, std::vector<sf::Sprite>& p_entity_drawings);
	//static void RocketFiringHandler(std::vector<std::shared_ptr<CEntity>>& p_rockets_on_orbits, std::vector<FP32>& p_rocket_firing_angles);
	//static void MonsterChaseOrbitron(std::vector<std::shared_ptr<CEntity>>& p_entity_list);
	std::vector<std::shared_ptr<CEntity>>& GetSleepingMonsters();
	std::vector<std::shared_ptr<CEntity>> GetEntityList();
	E_STATES GetGameState();
};