#include "CTimer.h"

CTimer::CTimer()
{
	this->ElapsedTimeRocketrightCache = sf::Time::Zero;
	this->ElapsedTimeBombAdditionCache = sf::Time::Zero;
	this->ElapsedTimeBombRemovalCache = sf::Time::Zero;
	this->ElapsedTimeMonsterOrbitChangeCache = sf::Time::Zero;
}

CTimer::~CTimer()
{

}

void CTimer::MonsterSleepTimingHandler(CConfigurationData& config_data, const sf::Clock& global_clock, CModel& model)
{
	for (INT32S i = 0; i < model.GetSleepingMonsters().size(); i++) {
		FP32 elapsed = global_clock.getElapsedTime().asSeconds() - this->GetMonsterSleepTimeBegin()[i].asSeconds() - this->GetMonsterSleepIdleTime()[i].asSeconds();
		if (elapsed > config_data.GetMonsterSleepTimeSec()) {
			model.GetSleepingMonsters()[i]->SetNumLife(model.GetSleepingMonsters()[i]->GetNumLife() + 1);
			model.GetSleepingMonsters()[i]->SetVelocity(config_data.GetMonsterVelocity());
			model.GetSleepingMonsters().erase(model.GetSleepingMonsters().begin() + i);
			this->GetMonsterSleepTimeBegin().erase(this->GetMonsterSleepTimeBegin().begin() + i);
			this->GetMonsterSleepIdleTime().erase(this->GetMonsterSleepIdleTime().begin() + i);
			i--;
		}else {

		}
	}
}

sf::Time& CTimer::GetElapsedTimeRocketright()
{
	return this->ElapsedTimeRocketright;
}

sf::Time& CTimer::GetElapsedTimeBombAddition()
{
	return this->ElapsedTimeBombAddition;
}

sf::Time& CTimer::GetElapsedTimeBombRemoval()
{
	return this->ElapsedTimeBombRemoval;
}

sf::Time& CTimer::GetElapsedTimeMonsterOrbitChange()
{
	return this->ElapsedTimeMonsterOrbitChange;
}

sf::Time& CTimer::GetElapsedTimeRocketrightCache()
{
	return this->ElapsedTimeRocketrightCache;
}
sf::Time& CTimer::GetElapsedTimeBombAdditionCache()
{
	return this->ElapsedTimeBombAdditionCache;
}

sf::Time& CTimer::GetElapsedTimeBombRemovalCache()
{
	return this->ElapsedTimeBombRemovalCache;
}
sf::Time& CTimer::GetElapsedTimeMonsterOrbitChangeCache()
{
	return this->ElapsedTimeMonsterOrbitChangeCache;
}

std::vector<sf::Time>& CTimer::GetMonsterSleepTimeBegin()
{
	return this->MonsterSleepTimeBegin;
}

std::vector<sf::Time>& CTimer::GetMonsterSleepIdleTime()
{
	return this->MonsterSleepIdleTime;
}

void CTimer::SetElapsedTimeRocketright(const sf::Time& time)
{
	this->ElapsedTimeRocketright = time;
}

void CTimer::SetElapsedTimeBombAddition(const sf::Time& time)
{
	this->ElapsedTimeBombAddition = time;
}

void CTimer::SetElapsedTimeBombRemoval(const sf::Time& time)
{
	this->ElapsedTimeBombRemoval = time;
}

void CTimer::SetElapsedTimeMonsterOrbitChange(const sf::Time& time)
{
	this->ElapsedTimeMonsterOrbitChange = time;
}

void CTimer::SetElapsedTimeRocketrightCache(const sf::Time& time)
{
	this->ElapsedTimeRocketrightCache = time;
}

void CTimer::SetElapsedTimeBombAdditionCache(const sf::Time& time)
{
	this->ElapsedTimeBombAdditionCache = time;
}

void CTimer::SetElapsedTimeBombRemovalCache(const sf::Time& time)
{
	this->ElapsedTimeBombRemovalCache = time;
}

void CTimer::SetElapsedTimeMonsterOrbitChangeCache(const sf::Time& time)
{
	this->ElapsedTimeMonsterOrbitChangeCache = time;
}

void CTimer::SetMonsterSleepTimeBegin(const std::vector<sf::Time>& time)
{
	this->MonsterSleepTimeBegin = time;
}

void CTimer::SetMonsterSleepIdleTime(const std::vector<sf::Time>& time)
{
	this->MonsterSleepIdleTime = time;
}