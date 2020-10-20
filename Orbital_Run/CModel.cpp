#include "CModel.h"

CModel::CModel()
{

}

CModel::CModel(CConfigurationData& config_data)
{
    this->NumOrbits = config_data.OrbitNumber;
    this->NumMonsters = config_data.MonsterNumber;
    this->VOrbitron = config_data.OrbitronVelocity;
    this->VMonster = config_data.MonsterVelocity;
}

CModel::~CModel()
{

}

void CModel::GenerateEntityOnRandomPoint(CConfigurationData& config_data, E_ENTITY_TYPES entity_type)
{
    INT32S random_orbit;
    INT32S range_min = 0;
    INT32S range_max = config_data.GetNumOrbits() - 1;
    BOOLEAN collision = false;
    FP32 random_angle, random_point_x, random_point_y, bounding_box_x, bounding_box_y;
    FP32 initial_x = WINDOW_CENTER_X - INNER_ORBIT_RADIUS + ORBITRON_INITIAL_ORBIT * DISTANCE_BTW_ORBITS;
    FP32 initial_y = WINDOW_CENTER_Y;
    FP32 x_shifted = initial_x - WINDOW_CENTER_X;
    FP32 y_shifted = initial_y - WINDOW_CENTER_Y;

    random_orbit = rand() % (range_max - range_min + 1) + range_min;
    do {
        random_angle = ANGLE_MIN + static_cast<FP32>(rand()) / (static_cast<FP32>(RAND_MAX / (ANGLE_MAX - ANGLE_MIN)));
        random_point_x = (INNER_ORBIT_RADIUS + DISTANCE_BTW_ORBITS * random_orbit) * COS(random_angle) + WINDOW_CENTER_X;
        random_point_y = (INNER_ORBIT_RADIUS + DISTANCE_BTW_ORBITS * random_orbit) * SIN(random_angle) + WINDOW_CENTER_Y;
        for (INT32S i = 0; i < this->EntityList.size(); i++) {
            bounding_box_x = this->EntityList[i]->GetPositionX();
            bounding_box_y = this->EntityList[i]->GetPositionY();
            if (random_point_x > bounding_box_x - BOUNDING_BOX_WIDTH / 2.0f && random_point_x < bounding_box_x + BOUNDING_BOX_WIDTH / 2.0f && random_point_y > bounding_box_y - BOUNDING_BOX_HEIGHT / 2.0f && random_point_y < bounding_box_y + BOUNDING_BOX_HEIGHT / 2.0f) {
                collision = true;
                break;
            }
            else {
                collision = false;
            }
        }
    } while (collision);

    //std::shared_ptr<CEntity> p_entity(new CEntity);
    //CEntity* p_entity = new CEntity;
    switch (entity_type) {
    case ENTITY_TYPES_ORBITRON:
    {
        std::shared_ptr<COrbitron> p_entity(new COrbitron);
        p_entity->Init(entity_type, WINDOW_CENTER_X + INNER_ORBIT_RADIUS + ORBITRON_INITIAL_ORBIT * DISTANCE_BTW_ORBITS, WINDOW_CENTER_Y, config_data.GetVOrbitron(), ENTITY_DRAWING_RADIUS, ANGLE_MIN, ORBITRON_INITIAL_ORBIT, config_data.OrbitronInitialLife, true, ENTITY_INITIAL_LITTLELIFE, ENTITY_INITIAL_ROCKET_RIGHT);
        this->EntityList.push_back(p_entity);
        break;
    }
    case ENTITY_TYPES_ROCKET:
    {
        std::shared_ptr<CRocket> p_entity(new CRocket);
        p_entity->Init(entity_type, random_point_x, random_point_y, config_data.GetVOrbitron() * config_data.RocketOrbitronVelocityRatio, ENTITY_DRAWING_RADIUS, random_angle, random_orbit, 1, true);
        this->EntityList.push_back(p_entity);
        break;
    }
    case ENTITY_TYPES_MONSTER:
    {
        std::shared_ptr<CMonster> p_entity(new CMonster);
        p_entity->Init(entity_type, random_point_x, random_point_y, config_data.GetVMonster(), ENTITY_DRAWING_RADIUS, random_angle, random_orbit, 1, true);
        this->EntityList.push_back(p_entity);
        break;
    }
    case ENTITY_TYPES_ROCKET_RIGHT:
    {
        std::shared_ptr<CRocketRight> p_entity(new CRocketRight);
        p_entity->Init(entity_type, random_point_x, random_point_y, config_data.GetVRocketRight(), ENTITY_DRAWING_RADIUS, random_angle, random_orbit, 1, true);
        this->EntityList.push_back(p_entity);
        break;
    }
    case ENTITY_TYPES_BOMB:
    {
        std::shared_ptr<CBomb> p_entity(new CBomb);
        p_entity->Init(entity_type, random_point_x, random_point_y, config_data.GetVBomb(), ENTITY_DRAWING_RADIUS, random_angle, random_orbit, 1, true);
        this->EntityList.push_back(p_entity);
        break;
    }
    case ENTITY_TYPES_LIFE:
    {
        std::shared_ptr<CLife> p_entity(new CLife);
        p_entity->Init(entity_type, random_point_x, random_point_y, config_data.GetVLife(), ENTITY_DRAWING_RADIUS, random_angle, random_orbit, 1, true);
        this->EntityList.push_back(p_entity);
        break;
    }
    default:
        break;
    }
    //CEntity temp_entity = *p_entity;
    //p_entity_list.push_back(p_entity);
    //delete p_entity;
}

//std::vector<std::vector<std::shared_ptr<CEntity>>> CModel::CollisionDetection(const std::vector<std::shared_ptr<CEntity>>& p_entity_list)
//{
//    std::vector<std::vector<std::shared_ptr<CEntity>>> collision_list;
//    FP32 distance;
//
//    for (INT32S i = 0; i < p_entity_list.size(); i++) {
//        for (INT32S j = i + 1; j < p_entity_list.size(); j++) {
//            if (p_entity_list[i]->GetIsAlive() && p_entity_list[j]->GetIsAlive() && p_entity_list[i]->GetNumLife() > 0 && p_entity_list[j]->GetNumLife() > 0) {
//                distance = EUCLIDEAN_DIST(p_entity_list[i]->GetPositionX(), p_entity_list[j]->GetPositionX(), p_entity_list[i]->GetPositionY(), p_entity_list[j]->GetPositionY());
//                if (distance <= 2 * ENTITY_DRAWING_RADIUS) {
//                    collision_list.push_back({ p_entity_list[i], p_entity_list[j] });
//                }
//            }
//        }
//    }
//    return collision_list;
//}
//
//void CModel::CollisionHandler(CConfigurationData& config_data, std::vector<std::vector<std::shared_ptr<CEntity>>>& p_collision_list, std::vector<E_COLLISION_TYPES>* p_collision_types, E_STATES& game_state, std::vector<std::shared_ptr<CEntity>>& p_sleeping_monsters, const sf::Clock& global_clock, sf::Clock& interrupt_clock, CTimer& timer)
//{
//    for (INT32S i = 0; i < p_collision_list.size(); i++) {
//        if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->EntityType == ENTITY_TYPES_MONSTER) {
//            p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetVelocity(0.0f);
//            //p_collision_list[i][1]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_MONSTER);
//
//            p_sleeping_monsters.push_back(p_collision_list[i][1]);
//            timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
//            timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
//
//            if (p_collision_list[i][0]->GetNumLife() == 0) {
//                game_state = STATES_GAME_OVER;
//                break;
//            }
//            else {
//                interrupt_clock.restart();
//                game_state = STATES_LOST_LIFE;
//                break;
//            }
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_MONSTER && p_collision_list[i][1]->EntityType == ENTITY_TYPES_ORBITRON) {
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][0]->SetVelocity(0.0f);
//            //p_collision_list[i][0]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_MONSTER);
//
//            p_sleeping_monsters.push_back(p_collision_list[i][0]);
//            timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
//            timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
//
//            if (p_collision_list[i][1]->GetNumLife() == 0) {
//                game_state = STATES_GAME_OVER;
//                break;
//            }
//            else {
//                interrupt_clock.restart();
//                game_state = STATES_LOST_LIFE;
//                break;
//            }
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->EntityType == ENTITY_TYPES_BOMB) {
//            p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_BOMB);
//            if (p_collision_list[i][0]->GetNumLife() == 0) {
//                game_state = STATES_GAME_OVER;
//                break;
//            }
//            else {
//                interrupt_clock.restart();
//                game_state = STATES_LOST_LIFE;
//                break;
//            }
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_BOMB && p_collision_list[i][1]->EntityType == ENTITY_TYPES_ORBITRON) {
//            p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][0]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_BOMB);
//            if (p_collision_list[i][1]->GetNumLife() == 0) {
//                game_state = STATES_GAME_OVER;
//                break;
//            }
//            else {
//                interrupt_clock.restart();
//                game_state = STATES_LOST_LIFE;
//                break;
//            }
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->EntityType == ENTITY_TYPES_LIFE) {
//            std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][0]));
//            p_orbitron->SetNumLittleLife(p_orbitron->GetNumLittleLife() + 1);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_LIFE);
//            if (p_orbitron->GetNumLittleLife() == config_data.LittlelifeNumForLife) {
//                p_orbitron->SetNumLife(p_orbitron->GetNumLife() + 1);
//                p_orbitron->SetNumLittleLife(0);
//            }
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_LIFE && p_collision_list[i][1]->EntityType == ENTITY_TYPES_ORBITRON) {
//            std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][1]));
//            p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
//            p_orbitron->SetNumLittleLife(p_orbitron->GetNumLittleLife() + 1);
//            p_collision_list[i][0]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_LIFE);
//            if (p_orbitron->GetNumLittleLife() == config_data.LittlelifeNumForLife) {
//                p_orbitron->SetNumLife(p_collision_list[i][1]->GetNumLife() + 1);
//                p_orbitron->SetNumLittleLife(0);
//            }
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_ORBITRON && p_collision_list[i][1]->EntityType == ENTITY_TYPES_ROCKET_RIGHT) {
//            std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][0]));
//            p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() + 1);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_ROCKETRIGHT);
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_ROCKET_RIGHT && p_collision_list[i][1]->EntityType == ENTITY_TYPES_ORBITRON) {
//            std::shared_ptr<COrbitron> p_orbitron = std::dynamic_pointer_cast<COrbitron>(std::shared_ptr<CEntity>(p_collision_list[i][1]));
//            p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
//            p_orbitron->SetNumRocketRight(p_orbitron->GetNumRocketRight() + 1);
//            p_collision_list[i][0]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_ORBITRON_ROCKETRIGHT);
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_MONSTER && p_collision_list[i][1]->EntityType == ENTITY_TYPES_ROCKET) {
//            p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
//            p_collision_list[i][0]->SetVelocity(0.0f);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetIsAlive(false);
//            p_collision_types->push_back(COLLISION_TYPES_MONSTER_ROCKET);
//
//            p_sleeping_monsters.push_back(p_collision_list[i][0]);
//            timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
//            timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
//        }
//        else if (p_collision_list[i][0]->EntityType == ENTITY_TYPES_ROCKET && p_collision_list[i][1]->EntityType == ENTITY_TYPES_MONSTER) {
//            p_collision_list[i][0]->SetNumLife(p_collision_list[i][0]->GetNumLife() - 1);
//            p_collision_list[i][0]->SetIsAlive(false);
//            //p_collision_list[i][1]->SetIsAlive(false);
//            p_collision_list[i][1]->SetNumLife(p_collision_list[i][1]->GetNumLife() - 1);
//            p_collision_list[i][1]->SetVelocity(0.0f);
//            p_collision_types->push_back(COLLISION_TYPES_MONSTER_ROCKET);
//
//            p_sleeping_monsters.push_back(p_collision_list[i][1]);
//            timer.GetMonsterSleepTimeBegin().push_back(global_clock.getElapsedTime());
//            timer.GetMonsterSleepIdleTime().push_back(sf::Time::Zero);
//        }
//    }
//}

void CModel::UpdateEntityList(std::vector<std::shared_ptr<CEntity>>& p_entity_list, std::vector<sf::Sprite>& p_entity_drawings)
{
    for (INT32S i = 0; i < p_entity_list.size(); i++) {
        if (!(p_entity_list[i]->GetIsAlive())) {
            p_entity_list.erase(p_entity_list.begin() + i);
            p_entity_drawings.erase(p_entity_drawings.begin() + i);
        }
    }
}

//void CModel::RocketFiringHandler(std::vector<std::shared_ptr<CEntity>>& p_rockets_on_orbits, std::vector<FP32>& p_rocket_firing_angles)
//{
//    FP32 angle_tolerance;
//    for (INT32S i = 0; i < p_rockets_on_orbits.size(); i++) {
//        angle_tolerance = p_rockets_on_orbits[i]->GetVelocity();
//        if (p_rockets_on_orbits[i]->GetIsAlive() && p_rockets_on_orbits[i]->GetAngle() >= p_rocket_firing_angles[i] && p_rockets_on_orbits[i]->GetAngle() < p_rocket_firing_angles[i] + angle_tolerance) {
//            p_rockets_on_orbits[i]->SetIsAlive(false);
//            p_rockets_on_orbits[i]->SetNumLife(0);
//            p_rockets_on_orbits.erase(p_rockets_on_orbits.begin() + i);
//            p_rocket_firing_angles.erase(p_rocket_firing_angles.begin() + i);
//            i--;
//        }
//        else if (!p_rockets_on_orbits[i]->GetIsAlive()) {
//            p_rockets_on_orbits.erase(p_rockets_on_orbits.begin() + i);
//            p_rocket_firing_angles.erase(p_rocket_firing_angles.begin() + i);
//            i--;
//        }
//    }
//}
//
//void CModel::MonsterChaseOrbitron(std::vector<std::shared_ptr<CEntity>>& entity_list)
//{
//    INT32S target_orbit = entity_list.front()->GetOrbit();
//    INT32S i, nearest_monster_index = 0;
//    FP32 smallest_distance = FLT_MAX;
//    FP32 cur_distance, cur_pos_x, cur_pos_y;
//    for (i = 0; i < entity_list.size(); i++) {
//        if (entity_list[i]->GetEntityType() == ENTITY_TYPES_MONSTER && entity_list[i]->GetNumLife() > 0 && entity_list[i]->GetOrbit() != target_orbit) {
//            cur_pos_x = entity_list[i]->GetPositionX();
//            cur_pos_y = entity_list[i]->GetPositionY();
//            cur_distance = EUCLIDEAN_DIST(cur_pos_x, entity_list.front()->GetPositionX(), cur_pos_y, entity_list.front()->GetPositionY());
//            if (cur_distance < smallest_distance) {
//                smallest_distance = cur_distance;
//                nearest_monster_index = i;
//            }
//        }
//    }
//
//    if (entity_list[nearest_monster_index]->GetOrbit() > target_orbit && entity_list[nearest_monster_index]->GetEntityType() == ENTITY_TYPES_MONSTER) {
//        std::shared_ptr<CMonster> p_monster = std::dynamic_pointer_cast<CMonster>(std::shared_ptr<CEntity>(entity_list[nearest_monster_index]));
//        p_monster->ChangeOrbit(DIRECTION_IN);
//    }
//    else if (entity_list[nearest_monster_index]->GetOrbit() < target_orbit && entity_list[nearest_monster_index]->GetEntityType() == ENTITY_TYPES_MONSTER){
//        std::shared_ptr<CMonster> p_monster = std::dynamic_pointer_cast<CMonster>(std::shared_ptr<CEntity>(entity_list[nearest_monster_index]));
//        p_monster->ChangeOrbit(DIRECTION_OUT);
//    }
//    else {
//
//    }
//}

std::vector<std::shared_ptr<CEntity>>& CModel::GetSleepingMonsters()
{
    return this->SleepingMonsters;
}

std::vector<std::shared_ptr<CEntity>> CModel::GetEntityList()
{
    return this->EntityList;
}

E_STATES CModel::GetGameState()
{
    return this->GameState;
}