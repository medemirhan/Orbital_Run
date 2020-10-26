#pragma once
#include <SFML/Graphics.hpp>

class CGame;
class CConfigurationData;
class CModel;

class CState {
protected:
	CState() {}; //no one but the class itself (and friends) should be able to create instances of it using that constructor
public:
	//Deleting a derived class object using a pointer of base class type that has a non-virtual destructor results in
	//undefined behavior. To correct this situation, the base class should be defined with a virtual destructor.
	virtual ~CState() {}
	virtual void OnStateHandler(CGame* game, sf::RenderWindow& app, CConfigurationData& config_data, CModel& model) = 0;
	virtual void OnEntry(CGame* game) = 0;
	virtual void OnExit(CGame* game) = 0;
};