#include "CControllerPlayingScreen.h"

CControllerPlayingScreen::CControllerPlayingScreen()
{

}

CControllerPlayingScreen::~CControllerPlayingScreen()
{

}

INT32S CControllerPlayingScreen::InvokeScreen(sf::RenderWindow& app, CConfigurationData& config_data, CModel& model)
{
	model.GameState = STATES_PLAYING_GAME;
	INT32S return_val = 2;
	BOOLEAN change_screen = false;
	sf::Clock global_clock;
	sf::Clock interrupt_clock;
	CConfigurationData updated_config_data(&config_data);
	CTimer timer;
	INT32S num_orbits = updated_config_data.GetOrbitNumber();
	INT32S num_monsters = updated_config_data.GetMonsterNumber();
	INT32S num_active_life = 0;

	std::vector<std::vector<std::shared_ptr<CEntity>>> collision_list;
	std::vector<E_COLLISION_TYPES> collision_types;

	CViewPlayingScreen view;
	view.SetSceneProperties();
	view.GenerateOrbitDrawings(updated_config_data);
	model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_ORBITRON);

	for (INT32S i = 0; i < num_monsters; i++) {
		model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_MONSTER);
	}
	sf::Clock clock_monster_orbit_change;

	model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_ROCKET_RIGHT);
	sf::Clock clock_rocketright;

	for (INT32S i = 0; i < updated_config_data.ConstantBombAdditionNumber; i++) {
		model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_BOMB);
	}
	sf::Clock clock_bomb_addition;
	sf::Clock clock_bomb_removal;

	for (INT32S i = 0; i < updated_config_data.ConstantLifeNumber; i++) {
		model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_LIFE);
		num_active_life++;
	}

	for (INT32S i = 0; i < model.EntityList.size(); i++) {
		view.GenerateEntityDrawings(updated_config_data, model.EntityList[i]);
	}

	while (app.isOpen()) {
		sf::Event event;
		while (app.pollEvent(event)) {
			return_val = this->UserInputHandler(event, view, config_data, model, timer, change_screen, global_clock, interrupt_clock, clock_rocketright, clock_bomb_addition, clock_bomb_removal, clock_monster_orbit_change, num_orbits);
			if (change_screen) {
				return return_val;
			}else {

			}
		}

		switch (model.GameState) {
		case STATES_PLAYING_GAME:
		{
			for (INT32S i = 0; i < model.EntityList.size(); i++) {
				if (model.EntityList[i]->GetIsAlive() && model.EntityList[i]->GetVelocity() > 0 && model.EntityList[i]->GetNumLife() > 0) {
					model.EntityList[i]->RotateEntity(WINDOW_CENTER_X, WINDOW_CENTER_Y);
				}else {

				}
			}
			model.GameLevel += model.EntityList.front()->GetVelocity() / ANGLE_MAX;

			timer.SetElapsedTimeMonsterOrbitChange(timer.GetElapsedTimeMonsterOrbitChangeCache() + clock_monster_orbit_change.getElapsedTime());
			if (timer.GetElapsedTimeMonsterOrbitChange().asSeconds() > updated_config_data.MonsterOrbitChangeIntervalSec) {
				this->MonsterChaseOrbitron(model.EntityList);
				timer.SetElapsedTimeMonsterOrbitChangeCache(sf::Time::Zero);
				clock_monster_orbit_change.restart();
			}else {

			}

			num_active_life = 0;
			for (INT32S i = 0; i < model.EntityList.size(); i++) {
				if (model.EntityList[i]->GetEntityType() == ENTITY_TYPES_LIFE) {
					num_active_life++;
				}else {

				}
			}

			if (num_active_life < updated_config_data.ConstantLifeNumber) {
				for (INT32S i = 0; i < updated_config_data.ConstantLifeNumber - num_active_life; i++) {
					model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_LIFE);
					view.GenerateEntityDrawings(updated_config_data, model.EntityList.back());
				}
				num_active_life = updated_config_data.ConstantLifeNumber;
			}else {

			}

			timer.SetElapsedTimeRocketright(timer.GetElapsedTimeRocketrightCache() + clock_rocketright.getElapsedTime());
			if (timer.GetElapsedTimeRocketright().asSeconds() > updated_config_data.RocketRightIntervalSec) {
				model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_ROCKET_RIGHT);
				view.GenerateEntityDrawings(updated_config_data, model.EntityList.back());
				timer.SetElapsedTimeRocketrightCache(sf::Time::Zero);
				clock_rocketright.restart();
			}else {

			}

			timer.SetElapsedTimeBombAddition(timer.GetElapsedTimeBombAdditionCache() + clock_bomb_addition.getElapsedTime());
			if (timer.GetElapsedTimeBombAddition().asSeconds() > updated_config_data.BombAdditionIntervalSec) {
				for (INT32S i = 0; i < updated_config_data.ConstantBombAdditionNumber; i++) {
					model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_BOMB);
					view.GenerateEntityDrawings(updated_config_data, model.EntityList.back());
				}
				timer.SetElapsedTimeBombAdditionCache(sf::Time::Zero);
				clock_bomb_addition.restart();
				//clock_bomb_removal.restart();
			}else {

			}

			timer.SetElapsedTimeBombRemoval(timer.GetElapsedTimeBombRemovalCache() + clock_bomb_removal.getElapsedTime());
			if (timer.GetElapsedTimeBombRemoval().asSeconds() > updated_config_data.BombRemovalIntervalSec) {
				INT32S bomb_removed = 0;
				for (INT32S i = 0; i < model.EntityList.size(); i++) {
					if (model.EntityList[i]->GetEntityType() == ENTITY_TYPES_BOMB && bomb_removed < updated_config_data.ConstantBombAdditionNumber) {
						//bombanýn biri remove edilmeden önce orbitronla çarpýþýp yokolduysa, bu bombanýn yerine henüz removal
						//süresi gelmemiþ bir bomba remove edilmiþ oluyor!
						model.EntityList.erase(model.EntityList.begin() + i);
						view.EntityDrawings.erase(view.EntityDrawings.begin() + i);
						i--;
						bomb_removed++;
					}else {

					}
				}
				timer.SetElapsedTimeBombRemovalCache(sf::Time::Zero);
				clock_bomb_removal.restart();
			}else {

			}

			if (model.RocketsOnOrbits.size() > 0) {
				try {
					this->RocketFiringHandler(model.RocketsOnOrbits, model.RocketFiringAngles);
				}
				catch (...) {
					continue;
				}
			}else {

			}

			collision_list = this->CollisionDetection(model.EntityList);

			if (collision_list.size() > 0) {
				this->CollisionHandler(updated_config_data, collision_list, &collision_types, model.GameState, model.SleepingMonsters, global_clock, interrupt_clock, timer);
			}else {

			}

			timer.MonsterSleepTimingHandler(config_data, global_clock, model);

			FP32 angle_tolerance = model.EntityList.front()->GetVelocity();
			if (model.EntityList.front()->GetAngle() >= ANGLE_MIN && model.EntityList.front()->GetAngle() < ANGLE_MIN + angle_tolerance) {
				for (INT32S i = 0; i < model.EntityList.size(); i++) {
					if (model.EntityList[i]->GetVelocity() > 0 && model.EntityList[i]->GetEntityType() != ENTITY_TYPES_BOMB) {
						model.EntityList[i]->SetVelocity(model.EntityList[i]->GetVelocity() + updated_config_data.VelocityIncreaseAtLevelUp);
					}else {

					}
				}
			}else {

			}
			break;
		}
		case STATES_LOST_LIFE:
		{
			break;
		}
		case STATES_GAME_OVER:
		{
			break;
		}
		case STATES_GAME_PAUSED:
		{
			break;
		}
		default:
			break;
		}

		std::vector<INT32S> idx = model.UpdateEntityList();
		view.UpdateEntityDrawings(idx);
		for (INT32S i = 0; i < model.EntityList.size(); i++) {
			view.EntityDrawings[i].setPosition(model.EntityList[i]->GetPositionX(), model.EntityList[i]->GetPositionY());
			view.EntityDrawings[i].setOrigin(view.EntityDrawings[i].getLocalBounds().width / 2.0f, view.EntityDrawings[i].getLocalBounds().height / 2.0f);
		}

		std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(model.EntityList.front()));
		INT32S indicator_num_life = model.EntityList.front()->GetNumLife();
		INT32S indicator_num_littlelife = p_orbitron->GetNumLittleLife();
		INT32S indicator_num_rocketright = p_orbitron->GetNumRocketRight();

		view.UpdateIndicatorsView(model.GameLevel, indicator_num_life, indicator_num_littlelife, indicator_num_rocketright);

		view.PrintScreen(app, model.EntityList, model.GameState, num_orbits);

		//std::mutex m;
		//app.setActive(false);
		//std::thread thread_print_screen(&CViewPlayingScreen::PrintScreen, view, std::ref(app), std::ref(model.EntityList), std::ref(model.GameState), num_orbits);
		//thread_print_screen.join();

		std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME_MSEC));
	}
	return -1;
}

INT32S CControllerPlayingScreen::UserInputHandler(sf::Event& event, CViewPlayingScreen& view, CConfigurationData& config_data, CModel& model, CTimer& timer, BOOLEAN& change_screen, sf::Clock& global_clock, sf::Clock& interrupt_clock, sf::Clock& clock_rocketright, sf::Clock& clock_bomb_addition, sf::Clock& clock_bomb_removal, sf::Clock& clock_monster_orbit_change, INT32S& num_orbits)
{
	if (event.type == sf::Event::Closed) {
		change_screen = true;
		return -1;
	}else {

	}
	if (event.type == sf::Event::KeyPressed) {
		std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(model.EntityList.front()));
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			if (model.GameState == STATES_PLAYING_GAME) {
				interrupt_clock.restart();
				timer.SetElapsedTimeRocketrightCache(timer.GetElapsedTimeRocketrightCache() + clock_rocketright.getElapsedTime());
				timer.SetElapsedTimeBombAdditionCache(timer.GetElapsedTimeBombAdditionCache() + clock_bomb_addition.getElapsedTime());
				timer.SetElapsedTimeBombRemovalCache(timer.GetElapsedTimeBombRemovalCache() + clock_bomb_removal.getElapsedTime());
				timer.SetElapsedTimeMonsterOrbitChangeCache(timer.GetElapsedTimeMonsterOrbitChangeCache() + clock_bomb_removal.getElapsedTime());
				model.GameState = STATES_GAME_PAUSED;
			}else {

			}
			break;
		case sf::Keyboard::Left:
			if (p_orbitron->GetOrbit() > 0 && model.GameState == STATES_PLAYING_GAME) {
				p_orbitron->ChangeOrbit(DIRECTION_IN);
			}else {

			}
			break;
		case sf::Keyboard::Right:
			if (p_orbitron->GetOrbit() < num_orbits - 1 && model.GameState == STATES_PLAYING_GAME) {
				p_orbitron->ChangeOrbit(DIRECTION_OUT);
			}else {

			}
			break;
		case sf::Keyboard::Space:
			if (model.GameState == STATES_PLAYING_GAME && p_orbitron->GetNumRocketRight() > 0) {
				//fire rocket
				model.GenerateEntityOnRandomPoint(config_data, ENTITY_TYPES_ROCKET);
				model.EntityList.back()->SetPosition(p_orbitron->GetPositionX(), p_orbitron->GetPositionY());
				model.EntityList.back()->SetOrbit(p_orbitron->GetOrbit());
				model.EntityList.back()->SetAngle(p_orbitron->GetAngle());
				p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() - 1);
				view.GenerateEntityDrawings(config_data, model.EntityList.back());
				model.RocketsOnOrbits.push_back(model.EntityList.back());
				model.RocketFiringAngles.push_back(p_orbitron->GetAngle());
			}else {

			}
			break;
		case sf::Keyboard::Return:
			if (model.GameState == STATES_GAME_PAUSED || model.GameState == STATES_LOST_LIFE) {
				clock_rocketright.restart();
				clock_bomb_addition.restart();
				clock_bomb_removal.restart();
				clock_monster_orbit_change.restart();
				for (INT32S i = 0; i < model.SleepingMonsters.size(); i++) {
					std::vector<sf::Time> temp_timer = timer.GetMonsterSleepIdleTime();
					temp_timer[i] += interrupt_clock.getElapsedTime();
					timer.SetMonsterSleepIdleTime(temp_timer);
				}
				model.GameState = STATES_PLAYING_GAME;
			}
			else if (model.GameState == STATES_GAME_OVER) {
				model.GameState = STATES_PLAYING_GAME;
				//buraya initial game_config deðerlerini çekeceði bir config dosyasý yolla
				change_screen = true;
				return 2;
			}else {

			}
			break;
		case sf::Keyboard::M:
			if (model.GameState == STATES_GAME_PAUSED || model.GameState == STATES_LOST_LIFE || model.GameState == STATES_GAME_OVER) {
				CConfigurationData* p_default_config = new CConfigurationData;
				config_data.SetOrbitNumber(p_default_config->GetOrbitNumber());
				config_data.SetMonsterNumber(p_default_config->GetMonsterNumber());
				config_data.SetOrbitronVelocity(p_default_config->GetOrbitronVelocity());
				config_data.SetMonsterVelocity(p_default_config->GetMonsterVelocity());
				delete p_default_config;
				change_screen = true;
				return 0;
			}else {

			}
		default:
			break;
		}
	}else {

	}
	return 2;
}

std::vector<std::vector<std::shared_ptr<CEntity>>> CControllerPlayingScreen::CollisionDetection(const std::vector<std::shared_ptr<CEntity>>& p_entity_list)
{
	std::vector<std::vector<std::shared_ptr<CEntity>>> collision_list;
	FP32 distance;

	for (INT32S i = 0; i < p_entity_list.size(); i++) {
		for (INT32S j = i + 1; j < p_entity_list.size(); j++) {
			if (p_entity_list[i]->GetIsAlive() && p_entity_list[j]->GetIsAlive() && p_entity_list[i]->GetNumLife() > 0 && p_entity_list[j]->GetNumLife() > 0) {
				distance = EUCLIDEAN_DIST(p_entity_list[i]->GetPositionX(), p_entity_list[j]->GetPositionX(), p_entity_list[i]->GetPositionY(), p_entity_list[j]->GetPositionY());
				if (distance <= 2 * ENTITY_DRAWING_RADIUS) {
					collision_list.push_back({ p_entity_list[i], p_entity_list[j] });
				}else {

				}
			}else {

			}
		}
	}
	return collision_list;
}

void CControllerPlayingScreen::CollisionHandler(CConfigurationData& config_data, std::vector<std::vector<std::shared_ptr<CEntity>>>& p_collision_list, std::vector<E_COLLISION_TYPES>* p_collision_types, E_STATES& game_state, std::vector<std::shared_ptr<CEntity>>& p_sleeping_monsters, const sf::Clock& global_clock, sf::Clock& interrupt_clock, CTimer& timer)
{
	for (INT32S i = 0; i < p_collision_list.size(); i++) {
		if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_MONSTER) {
			p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][1]->SetVelocity(0.0f);
			//p_collision_list[i][1]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_MONSTER);

			p_sleeping_monsters.push_back(p_collision_list[i][1]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);

			if (p_collision_list[i][0]->GetNumLife() == 0) {
				game_state = STATES_GAME_OVER;
				break;
			}else {
				interrupt_clock.restart();
				game_state = STATES_LOST_LIFE;
				break;
			}
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_MONSTER && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][0]->SetVelocity(0.0f);
			//p_collision_list[i][0]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_MONSTER);

			p_sleeping_monsters.push_back(p_collision_list[i][0]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);

			if (p_collision_list[i][1]->GetNumLife() == 0) {
				game_state = STATES_GAME_OVER;
				break;
			}else {
				interrupt_clock.restart();
				game_state = STATES_LOST_LIFE;
				break;
			}
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_BOMB) {
			p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][1]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_BOMB);
			if (p_collision_list[i][0]->GetNumLife() == 0) {
				game_state = STATES_GAME_OVER;
				break;
			}else {
				interrupt_clock.restart();
				game_state = STATES_LOST_LIFE;
				break;
			}
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_BOMB && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][0]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_BOMB);
			if (p_collision_list[i][1]->GetNumLife() == 0) {
				game_state = STATES_GAME_OVER;
				break;
			}else {
				interrupt_clock.restart();
				game_state = STATES_LOST_LIFE;
				break;
			}
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_LIFE) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][0]));
			p_orbitron->SetNumLittleLife(p_orbitron->GetNumLittleLife() + 1);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][1]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_LIFE);
			if (p_orbitron->GetNumLittleLife() == config_data.LittlelifeNumForLife) {
				p_orbitron->SetNumLife(p_orbitron->GetNumLife() + 1);
				p_orbitron->SetNumLittleLife(0);
			}else {

			}
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_LIFE && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][1]));
			p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
			p_orbitron->SetNumLittleLife(p_orbitron->GetNumLittleLife() + 1);
			p_collision_list[i][0]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_LIFE);
			if (p_orbitron->GetNumLittleLife() == config_data.LittlelifeNumForLife) {
				p_orbitron->SetNumLife(p_collision_list[i][1]->GetNumLife() + 1);
				p_orbitron->SetNumLittleLife(0);
			}else {

			}
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ROCKET_RIGHT) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][0]));
			p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() + 1);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][1]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_ROCKETRIGHT);
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ROCKET_RIGHT && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][1]));
			p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
			p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() + 1);
			p_collision_list[i][0]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_ORBITRON_ROCKETRIGHT);
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_MONSTER && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ROCKET) {
			p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
			p_collision_list[i][0]->SetVelocity(0.0f);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][1]->SetIsAlive(false);
			p_collision_types->push_back(COLLISION_TYPES_MONSTER_ROCKET);

			p_sleeping_monsters.push_back(p_collision_list[i][0]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
		}else if (p_collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ROCKET && p_collision_list[i][1]->GetEntityType() == ENTITY_TYPES_MONSTER) {
			p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
			p_collision_list[i][0]->SetIsAlive(false);
			//p_collision_list[i][1]->SetIsAlive(false);
			p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
			p_collision_list[i][1]->SetVelocity(0.0f);
			p_collision_types->push_back(COLLISION_TYPES_MONSTER_ROCKET);

			p_sleeping_monsters.push_back(p_collision_list[i][1]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
		}else {

			}
	}
}

void CControllerPlayingScreen::RocketFiringHandler(std::vector<std::shared_ptr<CEntity>>& p_rockets_on_orbits, std::vector<FP32>& p_rocket_firing_angles)
{
	FP32 angle_tolerance;
	for (INT32S i = 0; i < p_rockets_on_orbits.size(); i++) {
		angle_tolerance = p_rockets_on_orbits[i]->GetVelocity();
		if (p_rockets_on_orbits[i]->GetIsAlive() && p_rockets_on_orbits[i]->GetAngle() >= p_rocket_firing_angles[i] && p_rockets_on_orbits[i]->GetAngle() < p_rocket_firing_angles[i] + angle_tolerance) {
			p_rockets_on_orbits[i]->SetIsAlive(false);
			p_rockets_on_orbits[i]->SetNumLife(0);
			p_rockets_on_orbits.erase(p_rockets_on_orbits.begin() + i);
			p_rocket_firing_angles.erase(p_rocket_firing_angles.begin() + i);
			i--;
		}else if (!p_rockets_on_orbits[i]->GetIsAlive()) {
			p_rockets_on_orbits.erase(p_rockets_on_orbits.begin() + i);
			p_rocket_firing_angles.erase(p_rocket_firing_angles.begin() + i);
			i--;
		}else {

		}
	}
}

void CControllerPlayingScreen::MonsterChaseOrbitron(std::vector<std::shared_ptr<CEntity>>& entity_list)
{
	INT32S target_orbit = entity_list.front()->GetOrbit();
	INT32S i, nearest_monster_index = 0;
	FP32 smallest_distance = FLT_MAX;
	FP32 cur_distance, cur_pos_x, cur_pos_y;
	for (i = 0; i < entity_list.size(); i++) {
		if (entity_list[i]->GetEntityType() == ENTITY_TYPES_MONSTER && entity_list[i]->GetNumLife() > 0 && entity_list[i]->GetOrbit() != target_orbit) {
			cur_pos_x = entity_list[i]->GetPositionX();
			cur_pos_y = entity_list[i]->GetPositionY();
			cur_distance = EUCLIDEAN_DIST(cur_pos_x, entity_list.front()->GetPositionX(), cur_pos_y, entity_list.front()->GetPositionY());
			if (cur_distance < smallest_distance) {
				smallest_distance = cur_distance;
				nearest_monster_index = i;
			}else {

			}
		}else {

		}
	}

	if (entity_list[nearest_monster_index]->GetOrbit() > target_orbit && entity_list[nearest_monster_index]->GetEntityType() == ENTITY_TYPES_MONSTER) {
		std::shared_ptr<CMonster> p_monster = std::dynamic_pointer_cast<CMonster>(std::shared_ptr<CEntity>(entity_list[nearest_monster_index]));
		p_monster->ChangeOrbit(DIRECTION_IN);
	}else if (entity_list[nearest_monster_index]->GetOrbit() < target_orbit && entity_list[nearest_monster_index]->GetEntityType() == ENTITY_TYPES_MONSTER) {
		std::shared_ptr<CMonster> p_monster = std::dynamic_pointer_cast<CMonster>(std::shared_ptr<CEntity>(entity_list[nearest_monster_index]));
		p_monster->ChangeOrbit(DIRECTION_OUT);
	}else {

	}
}