#pragma once
#include <SFML/Graphics.hpp>

class CGame;
class CConfigurationData;
class CModel;

class CState {
protected:
	CState() {};
public:
	virtual ~CState() {}
	virtual void OnStateHandler(CGame* game, sf::RenderWindow& app, CConfigurationData& config_data, CModel& model) = 0;
	virtual void OnEntry(CGame* game) = 0;
	virtual void OnExit(CGame* game) = 0;
};