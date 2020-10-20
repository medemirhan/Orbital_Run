#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "type_definitions.h"

#define GET_VARIABLE_NAME(var)    (#var)

class CConfigurationData
{
private:
	std::string Filename;
	BOOLEAN ConfigFileErrorStatus;
public:
	CConfigurationData();
	CConfigurationData(const CConfigurationData* config_data);
	~CConfigurationData();
	void XMLParser();
	void SetNumOrbits(INT32S num_orbit);
	void SetNumMonsters(INT32S num_monster);
	void SetVOrbitron(FP32 v_orbitron);
	void SetVMonster(FP32 v_monster);

	FP32 OrbitronInitialVelocity;
	FP32 MonsterInitialVelocity;
	FP32 RocketOrbitronVelocityRatio;
	FP32 VelocityIncreaseAtLevelUp;
	FP32 MonsterOrbitChangeIntervalSec;
	FP32 MonsterSleepTimeSec;
	INT32S OrbitronInitialLife;
	INT32S OrbitNumber;
	INT32S MonsterNumber;
	INT32S ConstantLifeCount;
	INT32S ConstantBombAdditionCount;
	INT32S RocketRightIntervalSec;
	INT32S BombAdditionIntervalSec;
	INT32S BombRemovalIntervalSec;
	INT32S LittlelifeNumForLife;
	FP32 OrbitronVelocity;
	FP32 MonsterVelocity;
	FP32 BombVelocity;
	FP32 RocketVelocity;
	FP32 RocketrightVelocity;
	FP32 LifeVelocity;

	BOOLEAN GetConfigFileErrorStatus() const;
	INT32S GetNumOrbits() const;
	INT32S GetNumMonsters() const;
	FP32 GetVOrbitron() const;
	FP32 GetVMonster() const;
	FP32 GetVBomb() const;
	FP32 GetVRocket() const;
	FP32 GetVRocketRight() const;
	FP32 GetVLife() const;
};

