#include "CControllerPlayingScreen.h"

CControllerPlayingScreen::CControllerPlayingScreen()
{

}

CControllerPlayingScreen::~CControllerPlayingScreen()
{

}

/* Controls the current state operations. Invokes UserInputHandler if a key pressed. Invokes CView to update view if needed. */
/* Returns an integer that indicates enum of State which will be assigned as current state. */
INT32S CControllerPlayingScreen::StateHandler(CGame& game, sf::RenderWindow& window, CConfigurationData& config_data, CModel& model)
{
	//game.SetState(CGame::pPlayingState);
	INT32S return_val = 2;
	BOOLEAN change_screen = false;
	sf::Clock global_clock;
	sf::Clock interrupt_clock;
	CConfigurationData updated_config_data(config_data);
	CTimer timer;
	INT32S num_orbits = updated_config_data.GetOrbitNumber();
	INT32S num_monsters = updated_config_data.GetMonsterNumber();
	INT32S num_active_life = 0;
	std::mutex mutex;

	std::vector<std::vector<std::shared_ptr<CEntity>>> collision_list;
	std::vector<E_COLLISION_TYPES> collision_types;

	//CViewPlayingScreen view;
	window.setActive(true);
	this->View.SetSceneProperties();
	this->View.GenerateOrbitDrawings(updated_config_data); /* Invoke View to draw orbits */
	model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_ORBITRON); /* Invoke Model to generate Orbitron */

	for (INT32S i = 0; i < num_monsters; i++) {
		model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_MONSTER); /* Invoke Model to generate Monsters */
	}
	sf::Clock clock_monster_orbit_change;

	model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_ROCKET_RIGHT); /* Invoke Model to generate RocketRights */
	sf::Clock clock_rocketright;

	for (INT32S i = 0; i < updated_config_data.GetConstantBombAdditionNumber(); i++) { /* Invoke Model to generate Bombs */
		model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_BOMB);
	}
	sf::Clock clock_bomb_addition;
	sf::Clock clock_bomb_removal;

	for (INT32S i = 0; i < updated_config_data.GetConstantLifeNumber(); i++) {
		model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_LIFE); /* Invoke Model to generate Lifes */
		num_active_life++;
	}

	for (INT32S i = 0; i < model.EntityList.size(); i++) {
		this->View.GenerateEntityDrawings(model.EntityList[i]); /* Invoke View to generate drawings depending on the Entity List stored by Model */
	}
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			return_val = this->UserInputHandler(game, event, config_data, model, timer, change_screen, global_clock, interrupt_clock, clock_rocketright, clock_bomb_addition, clock_bomb_removal, clock_monster_orbit_change, num_orbits);
			if (change_screen) {   /* change_screen might be updated in the UserInputHandler function */
				return return_val; /* If so, change the State */
			}else {

			}
		}

		if (!game.GetFlagGameOver() && !game.GetFlagLostLife() && !game.GetFlagGamePaused()) { /* If game is not interrupted (i.e. no game over, no pause, no lose life), run below */
			for (INT32S i = 0; i < model.EntityList.size(); i++) {
				if (model.EntityList[i]->GetIsAlive() && model.EntityList[i]->GetVelocity() > 0 && model.EntityList[i]->GetNumLife() > 0) {
					model.EntityList[i]->RotateEntity(WINDOW_CENTER_X, WINDOW_CENTER_Y);
				}
				else {

				}
			}
			model.SetGameLevel(model.GetGameLevel() + model.EntityList.front()->GetVelocity() / ANGLE_MAX); /* Invoke model to calculate game level depending on the current angle of the orbitron. Every full lap increases game level by 1 */

			timer.SetElapsedTimeMonsterOrbitChange(timer.GetElapsedTimeMonsterOrbitChangeCache() + clock_monster_orbit_change.getElapsedTime());
			if (timer.GetElapsedTimeMonsterOrbitChange().asSeconds() > updated_config_data.GetMonsterOrbitChangeIntervalSec()) {
				this->OrbitronChasingHandler(model.EntityList); /* Invoke OrbitronChasingHandler with a predefined period */
				timer.SetElapsedTimeMonsterOrbitChangeCache(sf::Time::Zero);
				clock_monster_orbit_change.restart();
			}
			else {

			}

			num_active_life = 0;
			for (INT32S i = 0; i < model.EntityList.size(); i++) {
				if (model.EntityList[i]->GetEntityType() == ENTITY_TYPES_LIFE) {
					num_active_life++;
				}
				else {

				}
			}

			if (num_active_life < updated_config_data.GetConstantLifeNumber()) { /* Lifes on the screen is kept constant always */
				for (INT32S i = 0; i < updated_config_data.GetConstantLifeNumber() - num_active_life; i++) {
					model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_LIFE); /* Invoke model to generate DBG_NEW life if it is below predefined constant number */
					this->View.GenerateEntityDrawings(model.EntityList.back());
				}
				num_active_life = updated_config_data.GetConstantLifeNumber();
			}
			else {

			}

			timer.SetElapsedTimeRocketright(timer.GetElapsedTimeRocketrightCache() + clock_rocketright.getElapsedTime());
			if (timer.GetElapsedTimeRocketright().asSeconds() > updated_config_data.GetRocketRightIntervalSec()) {
				model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_ROCKET_RIGHT); /* Invoke model to generate DBG_NEW rocket right at a predefined period */
				this->View.GenerateEntityDrawings(model.EntityList.back());
				timer.SetElapsedTimeRocketrightCache(sf::Time::Zero);
				clock_rocketright.restart();
			}
			else {

			}

			timer.SetElapsedTimeBombAddition(timer.GetElapsedTimeBombAdditionCache() + clock_bomb_addition.getElapsedTime());
			if (timer.GetElapsedTimeBombAddition().asSeconds() > updated_config_data.GetBombAdditionIntervalSec()) {
				for (INT32S i = 0; i < updated_config_data.GetConstantBombAdditionNumber(); i++) {
					model.GenerateEntityOnRandomPoint(updated_config_data, ENTITY_TYPES_BOMB); /* Invoke model to generate DBG_NEW bombs at a predefined period */
					this->View.GenerateEntityDrawings(model.EntityList.back());
				}
				timer.SetElapsedTimeBombAdditionCache(sf::Time::Zero);
				clock_bomb_addition.restart();
				//clock_bomb_removal.restart();
			}
			else {

			}

			timer.SetElapsedTimeBombRemoval(timer.GetElapsedTimeBombRemovalCache() + clock_bomb_removal.getElapsedTime());
			if (timer.GetElapsedTimeBombRemoval().asSeconds() > updated_config_data.GetBombRemovalIntervalSec()) {
				INT32S bomb_removed = 0;
				for (INT32S i = 0; i < model.EntityList.size(); i++) {
					if (model.EntityList[i]->GetEntityType() == ENTITY_TYPES_BOMB && bomb_removed < updated_config_data.ConstantBombAdditionNumber) {
						//bombanýn biri remove edilmeden önce orbitronla çarpýþýp yokolduysa, bu bombanýn yerine henüz removal
						//süresi gelmemiþ bir bomba remove edilmiþ oluyor. kontrol et!
						model.EntityList.erase(model.EntityList.begin() + i); /* Invoke model to remove bombs at a predefined period */
						this->View.EntityDrawings.erase(this->View.EntityDrawings.begin() + i);
						i--;
						bomb_removed++;
					}
					else {

					}
				}
				timer.SetElapsedTimeBombRemovalCache(sf::Time::Zero);
				clock_bomb_removal.restart();
			}
			else {

			}

			if (model.RocketsOnOrbits.size() > 0) { /* Invoke RocketFiringHandler if at least a rocket is fired and moving on orbits */
				try {
					this->RocketFiringHandler(model.RocketsOnOrbits, model.RocketFiringAngles);
				}
				catch (...) {
					continue;
				}
			}
			else {

			}

			collision_list = this->CollisionDetection(model.EntityList); /* Invoke CollisionDetection to check collisions at the moment */

			if (collision_list.size() > 0) { /* Invoke CollisionHandler if collision list is not empty */
				this->CollisionHandler(game, updated_config_data, collision_list, collision_types, model.SleepingMonsters, global_clock, interrupt_clock, timer);
			}
			else {

			}

			timer.MonsterSleepTimingHandler(config_data, global_clock, model); /* If there is a sleeping monster (i.e. shot by rocket or collided with orbitron), its wake time is handled by MonsterSleepTimingHandler */

			FP32 angle_tolerance = model.EntityList.front()->GetVelocity();
			if (model.EntityList.front()->GetAngle() >= ANGLE_MIN && model.EntityList.front()->GetAngle() < ANGLE_MIN + angle_tolerance) { /* This if block invokes Model to increase game level (entity velocities) at every full lap of Orbitron */
				for (INT32S i = 0; i < model.EntityList.size(); i++) {
					if (model.EntityList[i]->GetVelocity() > 0 && model.EntityList[i]->GetEntityType() != ENTITY_TYPES_BOMB) {
						model.EntityList[i]->SetVelocity(model.EntityList[i]->GetVelocity() + updated_config_data.GetVelocityIncreaseAtLevelUp());
					}
					else {

					}
				}
			}
			else {

			}
		}else {

		}

		std::vector<INT32S> idx = model.UpdateEntityList(); /* Invoke Model to remove entities which is not alive as a result of above operations */
		this->View.UpdateEntityDrawings(idx); /* Invoke View to stay up to date with the Model's EntityList */
		for (INT32S i = 0; i < model.EntityList.size(); i++) {
			this->View.EntityDrawings[i].setPosition(model.EntityList[i]->GetPositionX(), model.EntityList[i]->GetPositionY());
			this->View.EntityDrawings[i].setOrigin(this->View.EntityDrawings[i].getLocalBounds().width / 2.0f, this->View.EntityDrawings[i].getLocalBounds().height / 2.0f);
		}

		std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(model.EntityList.front())); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
		INT32S indicator_num_life = model.EntityList.front()->GetNumLife();
		INT32S indicator_num_littlelife = p_orbitron->GetNumLittleLife();
		INT32S indicator_num_rocketright = p_orbitron->GetNumRocketRight();

		this->View.UpdateIndicatorsView(model.GetGameLevel(), indicator_num_life, indicator_num_littlelife, indicator_num_rocketright);

		this->View.PrintScreen(game, window, model.GetEntityList(), num_orbits); /* Invoke View to print current scene */

		//window.setActive(false);
		//std::thread thread_print_screen(&CViewPlayingScreen::PrintScreen, std::ref(view), std::ref(window), std::ref(model.EntityList), std::ref(model.GameState), num_orbits, std::ref(mutex));
		//thread_print_screen.join();

		std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME_MSEC));
	}
	return STATES_EXIT; /* If the while loop above exits, this means that window is closed. */
}

/* Takes Event as argument and performs necessary actions depending on the user button press */
INT32S CControllerPlayingScreen::UserInputHandler(CGame& game, sf::Event& event, CConfigurationData& config_data, CModel& model, CTimer& timer, BOOLEAN& change_screen, sf::Clock& global_clock, sf::Clock& interrupt_clock, sf::Clock& clock_rocketright, sf::Clock& clock_bomb_addition, sf::Clock& clock_bomb_removal, sf::Clock& clock_monster_orbit_change, INT32S& num_orbits)
{
	if (event.type == sf::Event::Closed) {
		change_screen = true;
		return STATES_EXIT;
	}else {

	}
	if (event.type == sf::Event::KeyPressed) {
		std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(model.EntityList.front())); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			if (!game.GetFlagGameOver() && !game.GetFlagLostLife() && !game.GetFlagGamePaused()) { /* If game is interrupted by Esc press, store current timer values to cache timers */
				interrupt_clock.restart();
				timer.SetElapsedTimeRocketrightCache(timer.GetElapsedTimeRocketrightCache() + clock_rocketright.getElapsedTime());
				timer.SetElapsedTimeBombAdditionCache(timer.GetElapsedTimeBombAdditionCache() + clock_bomb_addition.getElapsedTime());
				timer.SetElapsedTimeBombRemovalCache(timer.GetElapsedTimeBombRemovalCache() + clock_bomb_removal.getElapsedTime());
				timer.SetElapsedTimeMonsterOrbitChangeCache(timer.GetElapsedTimeMonsterOrbitChangeCache() + clock_bomb_removal.getElapsedTime());
				game.SetFlagGamePaused(true);
			}else {

			}
			break;
		case sf::Keyboard::Left:
			if (p_orbitron->GetOrbit() > 0 && !game.GetFlagGameOver() && !game.GetFlagLostLife() && !game.GetFlagGamePaused()) {
				p_orbitron->ChangeOrbit(DIRECTION_IN);
			}else {

			}
			break;
		case sf::Keyboard::Right:
			if (p_orbitron->GetOrbit() < num_orbits - 1 && !game.GetFlagGameOver() && !game.GetFlagLostLife() && !game.GetFlagGamePaused()) {
				p_orbitron->ChangeOrbit(DIRECTION_OUT);
			}else {

			}
			break;
		case sf::Keyboard::Space: /* Fire rocket if below condition is met */
			if (p_orbitron->GetNumRocketRight() > 0 && !game.GetFlagGameOver() && !game.GetFlagLostLife() && !game.GetFlagGamePaused()) {
				model.GenerateEntityOnRandomPoint(config_data, ENTITY_TYPES_ROCKET);
				model.EntityList.back()->SetPosition(p_orbitron->GetPositionX(), p_orbitron->GetPositionY());
				model.EntityList.back()->SetOrbit(p_orbitron->GetOrbit());
				model.EntityList.back()->SetAngle(p_orbitron->GetAngle());
				p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() - 1);
				this->View.GenerateEntityDrawings(model.EntityList.back());
				model.RocketsOnOrbits.push_back(model.EntityList.back());
				model.RocketFiringAngles.push_back(p_orbitron->GetAngle());
			}else {

			}
			break;
		case sf::Keyboard::Return:
			if (game.GetFlagGamePaused()) {
				clock_rocketright.restart();
				clock_bomb_addition.restart();
				clock_bomb_removal.restart();
				clock_monster_orbit_change.restart();
				for (INT32S i = 0; i < model.SleepingMonsters.size(); i++) {
					std::vector<sf::Time> temp_timer = timer.GetMonsterSleepIdleTime();
					temp_timer[i] += interrupt_clock.getElapsedTime();
					timer.SetMonsterSleepIdleTime(temp_timer);
				}
				game.SetFlagGamePaused(false);
			}else if (game.GetFlagLostLife()) {
				clock_rocketright.restart();
				clock_bomb_addition.restart();
				clock_bomb_removal.restart();
				clock_monster_orbit_change.restart();
				for (INT32S i = 0; i < model.SleepingMonsters.size(); i++) {
					std::vector<sf::Time> temp_timer = timer.GetMonsterSleepIdleTime();
					temp_timer[i] += interrupt_clock.getElapsedTime();
					timer.SetMonsterSleepIdleTime(temp_timer);
				}
				game.SetFlagLostLife(false);
			}else if (game.GetFlagGameOver()) {
				game.SetFlagGameOver(false);
				change_screen = true;
				return STATES_PLAYING_SCREEN;
			}else {

			}
			break;
		case sf::Keyboard::M:
			if (game.GetFlagGamePaused() || game.GetFlagLostLife() || game.GetFlagGameOver()) {
				CConfigurationData* p_default_config = DBG_NEW CConfigurationData;
				config_data.SetOrbitNumber(p_default_config->GetOrbitNumber());
				config_data.SetMonsterNumber(p_default_config->GetMonsterNumber());
				config_data.SetOrbitronVelocity(p_default_config->GetOrbitronVelocity());
				config_data.SetMonsterVelocity(p_default_config->GetMonsterVelocity());
				delete p_default_config;
				change_screen = true;
				if (game.GetFlagGamePaused()) {
					game.SetFlagGamePaused(false);
				}else if (game.GetFlagLostLife()) {
					game.SetFlagLostLife(false);
				}else if (game.GetFlagGameOver()) {
					game.SetFlagGameOver(false);
				}else {

				}
				return STATES_MAIN_MENU;
			}else {

			}
		default:
			break;
		}
	}else {

	}

	return STATES_PLAYING_SCREEN; /* If above If statements don't change the state, return current state */
}

/* Checks Model's EntityList to see whether any entity pair is collided and returns a 2D vector that stores collision list */
/* It uses Euclidean Distance between entities to decide collision */
std::vector<std::vector<std::shared_ptr<CEntity>>> CControllerPlayingScreen::CollisionDetection(const std::vector<std::shared_ptr<CEntity>>& entity_list)
{
	std::vector<std::vector<std::shared_ptr<CEntity>>> collision_list;
	FP32 distance;

	for (INT32S i = 0; i < entity_list.size(); i++) {
		for (INT32S j = i + 1; j < entity_list.size(); j++) {
			if (entity_list[i]->GetIsAlive() && entity_list[j]->GetIsAlive() && entity_list[i]->GetNumLife() > 0 && entity_list[j]->GetNumLife() > 0) {
				distance = EUCLIDEAN_DIST(entity_list[i]->GetPositionX(), entity_list[j]->GetPositionX(), entity_list[i]->GetPositionY(), entity_list[j]->GetPositionY());
				if (distance <= 2 * ENTITY_DRAWING_RADIUS) {
					collision_list.push_back({ entity_list[i], entity_list[j] });
				}else {

				}
			}else {

			}
		}
	}
	return collision_list;
}

/* Takes collision list as argument and performs necessary operations such as decreasing collided entities' lifes, */
/* set FlagLostLife to true, start MonsterSleepTimer etc. */
void CControllerPlayingScreen::CollisionHandler(CGame& game, CConfigurationData& config_data, std::vector<std::vector<std::shared_ptr<CEntity>>>& collision_list, std::vector<E_COLLISION_TYPES>& collision_types, std::vector<std::shared_ptr<CEntity>>& sleeping_monsters, const sf::Clock& global_clock, sf::Clock& interrupt_clock, CTimer& timer)
{
	for (INT32S i = 0; i < collision_list.size(); i++) {
		if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_MONSTER) {
			collision_list[i][0]->SetNumLife(collision_list[i][0]->GetNumLife() - 1);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][1]->SetVelocity(0.0f);
			//collision_list[i][1]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_MONSTER);

			sleeping_monsters.push_back(collision_list[i][1]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);

			if (collision_list[i][0]->GetNumLife() == 0) {
				game.SetFlagGameOver(true);
				break;
			}else {
				interrupt_clock.restart();
				game.SetFlagLostLife(true);
				break;
			}
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_MONSTER && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][0]->SetVelocity(0.0f);
			//collision_list[i][0]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_MONSTER);

			sleeping_monsters.push_back(collision_list[i][0]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);

			if (collision_list[i][1]->GetNumLife() == 0) {
				game.SetFlagGameOver(true);
				break;
			}else {
				interrupt_clock.restart();
				game.SetFlagLostLife(true);
				break;
			}
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_BOMB) {
			collision_list[i][0]->SetNumLife(collision_list[i][0]->GetNumLife() - 1);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][1]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_BOMB);
			if (collision_list[i][0]->GetNumLife() == 0) {
				game.SetFlagGameOver(true);
				break;
			}else {
				interrupt_clock.restart();
				game.SetFlagLostLife(true);
				break;
			}
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_BOMB && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			collision_list[i][0]->SetNumLife(collision_list[i][0]->GetNumLife() - 1);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][0]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_BOMB);
			if (collision_list[i][1]->GetNumLife() == 0) {
				game.SetFlagGameOver(true);
				break;
			}else {
				interrupt_clock.restart();
				game.SetFlagLostLife(true);
				break;
			}
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_LIFE) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(collision_list[i][0])); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
			p_orbitron->SetNumLittleLife(p_orbitron->GetNumLittleLife() + 1);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][1]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_LIFE);
			if (p_orbitron->GetNumLittleLife() == config_data.LittlelifeNumForLife) {
				p_orbitron->SetNumLife(p_orbitron->GetNumLife() + 1);
				p_orbitron->SetNumLittleLife(0);
			}else {

			}
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_LIFE && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(collision_list[i][1])); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
			collision_list[i][0]->SetNumLife(collision_list[i][0]->GetNumLife() - 1);
			p_orbitron->SetNumLittleLife(p_orbitron->GetNumLittleLife() + 1);
			collision_list[i][0]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_LIFE);
			if (p_orbitron->GetNumLittleLife() == config_data.LittlelifeNumForLife) {
				p_orbitron->SetNumLife(collision_list[i][1]->GetNumLife() + 1);
				p_orbitron->SetNumLittleLife(0);
			}else {

			}
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ORBITRON && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ROCKET_RIGHT) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(collision_list[i][0])); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
			p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() + 1);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][1]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_ROCKETRIGHT);
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ROCKET_RIGHT && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ORBITRON) {
			std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(collision_list[i][1])); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
			collision_list[i][0]->SetNumLife(collision_list[i][0]->GetNumLife() - 1);
			p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() + 1);
			collision_list[i][0]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_ORBITRON_ROCKETRIGHT);
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_MONSTER && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_ROCKET) {
			collision_list[i][0]->SetNumLife(collision_list[i][0]->GetNumLife() - 1);
			collision_list[i][0]->SetVelocity(0.0f);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][1]->SetIsAlive(false);
			collision_types.push_back(COLLISION_TYPES_MONSTER_ROCKET);

			sleeping_monsters.push_back(collision_list[i][0]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
		}else if (collision_list[i][0]->GetEntityType() == ENTITY_TYPES_ROCKET && collision_list[i][1]->GetEntityType() == ENTITY_TYPES_MONSTER) {
			collision_list[i][0]->SetNumLife(collision_list[i][0]->GetNumLife() - 1);
			collision_list[i][0]->SetIsAlive(false);
			//collision_list[i][1]->SetIsAlive(false);
			collision_list[i][1]->SetNumLife(collision_list[i][1]->GetNumLife() - 1);
			collision_list[i][1]->SetVelocity(0.0f);
			collision_types.push_back(COLLISION_TYPES_MONSTER_ROCKET);

			sleeping_monsters.push_back(collision_list[i][1]);
			timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
			timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
		}else {

			}
	}
}

/* Takes rockets on orbits list and rocket firing angles, decides whether a rocket completed a complete lap without hitting any monster */
/* If so, rocket is removed from the scene */
void CControllerPlayingScreen::RocketFiringHandler(std::vector<std::shared_ptr<CEntity>>& rockets_on_orbits, std::vector<FP32>& rocket_firing_angles)
{
	FP32 angle_tolerance;
	for (INT32S i = 0; i < rockets_on_orbits.size(); i++) {
		angle_tolerance = rockets_on_orbits[i]->GetVelocity();
		if (rockets_on_orbits[i]->GetIsAlive() && rockets_on_orbits[i]->GetAngle() >= rocket_firing_angles[i] && rockets_on_orbits[i]->GetAngle() < rocket_firing_angles[i] + angle_tolerance) {
			rockets_on_orbits[i]->SetIsAlive(false);
			rockets_on_orbits[i]->SetNumLife(0);
			rockets_on_orbits.erase(rockets_on_orbits.begin() + i);
			rocket_firing_angles.erase(rocket_firing_angles.begin() + i);
			i--;
		}else if (!rockets_on_orbits[i]->GetIsAlive()) {
			rockets_on_orbits.erase(rockets_on_orbits.begin() + i);
			rocket_firing_angles.erase(rocket_firing_angles.begin() + i);
			i--;
		}else {

		}
	}
}


/* Takes entity list as argument and controls Euclidean distances of Orbitron and Monsters at closest orbits with Orbitron */
/* Then invokes ChangeOrbit function of the Monster which has the minimum distance to the Orbitron */
void CControllerPlayingScreen::OrbitronChasingHandler(std::vector<std::shared_ptr<CEntity>>& entity_list)
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
		std::shared_ptr<CMonster> p_monster = std::dynamic_pointer_cast<CMonster>(std::shared_ptr<CEntity>(entity_list[nearest_monster_index])); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
		p_monster->ChangeOrbit(DIRECTION_IN);
	}else if (entity_list[nearest_monster_index]->GetOrbit() < target_orbit && entity_list[nearest_monster_index]->GetEntityType() == ENTITY_TYPES_MONSTER) {
		std::shared_ptr<CMonster> p_monster = std::dynamic_pointer_cast<CMonster>(std::shared_ptr<CEntity>(entity_list[nearest_monster_index])); /* Casting is applied in order to access derived class (such as COrbitron, CMonster etc.) pointers which are holded in a container (EntityList) of base class pointers (CEntity) */
		p_monster->ChangeOrbit(DIRECTION_OUT);
	}else {

	}
}
