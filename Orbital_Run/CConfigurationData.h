#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "type_definitions.h"

class CConfigurationData {
private:
	std::string Filename;
	BOOLEAN ConfigFileErrorStatus;
public:
	FP32 OrbitronInitialVelocity;
	FP32 MonsterInitialVelocity;
	FP32 RocketOrbitronVelocityRatio;
	FP32 VelocityIncreaseAtLevelUp;
	FP32 MonsterOrbitChangeIntervalSec;
	FP32 MonsterSleepTimeSec;
	INT32S OrbitronInitialLife;
	INT32S OrbitNumber;
	INT32S MonsterNumber;
	INT32S ConstantLifeNumber;
	INT32S ConstantBombAdditionNumber;
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

	CConfigurationData();
	CConfigurationData(std::string file_name);
	CConfigurationData(const CConfigurationData& config_data);
	~CConfigurationData();
	void XMLParser();
	void SetFilename(std::string filename);
	void SetConfigFileErrorStatus(BOOLEAN status);
	void SetOrbitronInitialVelocity(FP32 velocity);
	void SetMonsterInitialVelocity(FP32 velocity);
	void SetRocketOrbitronVelocityRatio(FP32 ratio);
	void SetVelocityIncreaseAtLevelUp(FP32 velocity_increase);
	void SetMonsterOrbitChangeIntervalSec(FP32 interval);
	void SetMonsterSleepTimeSec(FP32 time);
	void SetOrbitronInitialLife(INT32S life);
	void SetOrbitNumber(INT32S orbit_number);
	void SetMonsterNumber(INT32S monster_number);
	void SetConstantLifeNumber(INT32S num);
	void SetConstantBombAdditionNumber(INT32S num);
	void SetRocketRightIntervalSec(INT32S interval);
	void SetBombAdditionIntervalSec(INT32S interval);
	void SetBombRemovalIntervalSec(INT32S interval);
	void SetLittlelifeNumForLife(INT32S littlelife_num);
	void SetOrbitronVelocity(FP32 velocity);
	void SetMonsterVelocity(FP32 velocity);
	void SetBombVelocity(FP32 velocity);
	void SetRocketVelocity(FP32 velocity);
	void SetRocketrightVelocity(FP32 velocity);
	void SetLifeVelocity(FP32 velocity);

	std::string GetFilename() const;
	BOOLEAN GetConfigFileErrorStatus() const;
	FP32 GetOrbitronInitialVelocity() const;
	FP32 GetMonsterInitialVelocity() const;
	FP32 GetRocketOrbitronVelocityRatio() const;
	FP32 GetVelocityIncreaseAtLevelUp() const;
	FP32 GetMonsterOrbitChangeIntervalSec() const;
	FP32 GetMonsterSleepTimeSec() const;
	INT32S GetOrbitronInitialLife() const;
	INT32S GetOrbitNumber() const;
	INT32S GetMonsterNumber() const;
	INT32S GetConstantLifeNumber() const;
	INT32S GetConstantBombAdditionNumber() const;
	INT32S GetRocketRightIntervalSec() const;
	INT32S GetBombAdditionIntervalSec() const;
	INT32S GetBombRemovalIntervalSec() const;
	INT32S GetLittlelifeNumForLife() const;
	FP32 GetOrbitronVelocity() const;
	FP32 GetMonsterVelocity() const;
	FP32 GetBombVelocity() const;
	FP32 GetRocketVelocity() const;
	FP32 GetRocketrightVelocity() const;
	FP32 GetLifeVelocity() const;
};

