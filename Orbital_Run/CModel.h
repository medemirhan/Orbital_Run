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
	friend class CControllerMainMenu;
	friend class CControllerConfigMenu;
	friend class CControllerPlayingScreen;
private:
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
	std::vector<INT32S> UpdateEntityList();

	void SetGameLevel(FP32 level);
	void SetNumOrbits(INT32S num_orbits);
	void SetNumMonsters(INT32S num_monsters);
	void SetVOrbitron(FP32 v_orbitron);
	void SetVMonster(FP32 v_monster);
	void SetEntityList(const std::vector<std::shared_ptr<CEntity>> p_entity_list);
	void SetRocketsOnOrbits(const std::vector<std::shared_ptr<CEntity>> p_rockets_on_orbits);
	void SetRocketFiringAngles(const std::vector<FP32>& angles);
	void SetSleepingMonsters(const std::vector<std::shared_ptr<CEntity>> p_sleeping_monster);

	FP32 GetGameLevel() const;
	INT32S GetNumOrbits() const;
	INT32S GetNumMonsters() const;
	FP32 GetVOrbitron() const;
	FP32 GetVMonster() const;
	std::vector<std::shared_ptr<CEntity>> GetEntityList() const;
	std::vector<std::shared_ptr<CEntity>> GetRocketsOnOrbits() const;
	std::vector<FP32> GetRocketFiringAngles() const;
	std::vector<std::shared_ptr<CEntity>>& GetSleepingMonsters();
};