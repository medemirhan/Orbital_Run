#pragma once
#include <SFML/Graphics.hpp>
#include "CViewPlayingScreen.h"
#include "type_definitions.h"

class CTimer {
private:
	sf::Time ElapsedTimeRocketright;
	sf::Time ElapsedTimeBombAddition;
	sf::Time ElapsedTimeBombRemoval;
	sf::Time ElapsedTimeMonsterOrbitChange;
	sf::Time ElapsedTimeRocketrightCache;
	sf::Time ElapsedTimeBombAdditionCache;
	sf::Time ElapsedTimeBombRemovalCache;
	sf::Time ElapsedTimeMonsterOrbitChangeCache;
	std::vector<sf::Time> MonsterSleepTimeBegin;
	std::vector<sf::Time> MonsterSleepIdleTime;
public:
	CTimer();
	~CTimer();
	void MonsterSleepTimingHandler(CConfigurationData& config_data, const sf::Clock& global_clock, CModel& model);
	sf::Time& GetElapsedTimeRocketright();
	sf::Time& GetElapsedTimeBombAddition();
	sf::Time& GetElapsedTimeBombRemoval();
	sf::Time& GetElapsedTimeMonsterOrbitChange();
	sf::Time& GetElapsedTimeRocketrightCache();
	sf::Time& GetElapsedTimeBombAdditionCache();
	sf::Time& GetElapsedTimeBombRemovalCache();
	sf::Time& GetElapsedTimeMonsterOrbitChangeCache();
	std::vector<sf::Time>& GetMonsterSleepTimeBegin();
	std::vector<sf::Time>& GetMonsterSleepIdleTime();

	void SetElapsedTimeRocketright(const sf::Time& time);
	void SetElapsedTimeBombAddition(const sf::Time& time);
	void SetElapsedTimeBombRemoval(const sf::Time& time);
	void SetElapsedTimeMonsterOrbitChange(const sf::Time& time);
	void SetElapsedTimeRocketrightCache(const sf::Time& time);
	void SetElapsedTimeBombAdditionCache(const sf::Time& time);
	void SetElapsedTimeBombRemovalCache(const sf::Time& time);
	void SetElapsedTimeMonsterOrbitChangeCache(const sf::Time& time);
	void SetMonsterSleepTimeBegin(const std::vector<sf::Time>& time);
	void SetMonsterSleepIdleTime(const std::vector<sf::Time>& time);

};

