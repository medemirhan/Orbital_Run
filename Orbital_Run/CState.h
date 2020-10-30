#pragma once
#include <SFML/Graphics.hpp>

class CGame;
class CConfigurationData;
class CModel;

class CState {
private:

public:
	CState() {}
	virtual ~CState() {}
	virtual void OnStateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) = 0;
	virtual void OnEntry(CGame& game) = 0;
	virtual void OnExit() = 0;
};