#pragma once
#include <SFML/Graphics.hpp>
#include "CController.h"
#include "CConfigurationData.h"
#include "CViewPlayingScreen.h"
#include <mutex>

class CControllerPlayingScreen : public CController {
private:
	CViewPlayingScreen* pView;
public:
	CControllerPlayingScreen();
	~CControllerPlayingScreen();
	INT32S StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model) override;
	INT32S UserInputHandler(CGame& game, sf::Event& event, CConfigurationData& config_data, CModel& model, CTimer& timer, BOOLEAN& change_screen, sf::Clock& global_clock, sf::Clock& interrupt_clock, sf::Clock& clock_rocketright, sf::Clock& clock_bomb_addition, sf::Clock& clock_bomb_removal, sf::Clock& clock_monster_orbit_change, INT32S& num_orbits);
	std::vector<std::vector<std::shared_ptr<CEntity>>> CollisionDetection(const std::vector<std::shared_ptr<CEntity>>& entity_list);
	void CollisionHandler(CGame& game, CConfigurationData& config_data, std::vector<std::vector<std::shared_ptr<CEntity>>>& collision_list, std::vector<E_COLLISION_TYPES>& collision_types, std::vector<std::shared_ptr<CEntity>>& sleeping_monsters, const sf::Clock& global_clock, sf::Clock& interrupt_clock, CTimer& timer);
	void RocketFiringHandler(std::vector<std::shared_ptr<CEntity>>& rockets_on_orbits, std::vector<FP32>& rocket_firing_angles);
	void OrbitronChasingHandler(std::vector<std::shared_ptr<CEntity>>& entity_list);
};