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
}

std::vector<INT32S> CModel::UpdateEntityList()
{
    std::vector<INT32S> idx;
    for (INT32S i = 0; i < this->EntityList.size(); i++) {
        if (!(this->EntityList[i]->GetIsAlive())) {
            this->EntityList.erase(this->EntityList.begin() + i);
            idx.push_back(i);
        }
    }
    return idx;
}

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