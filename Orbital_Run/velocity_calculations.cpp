#include "velocity_calculations.h"
#include "type_definitions.h"
#include <cmath>

#if TEST_MODE_ENABLED

void GetEntityAngles(CModel *p_model)
{
	angle_orbitron = p_model->GetEntityList()[0]->GetAngle();

	for (INT32S i = 0; i < p_model->GetEntityList().size(); i++) {
		if (p_model->GetEntityList()[i]->GetEntityType() == ENTITY_TYPES_MONSTER) {
			angle_monster = p_model->GetEntityList()[i]->GetAngle();
			break;
		}
		else {

		}
	}

	for (INT32S i = 0; i < p_model->GetEntityList().size(); i++) {
		if (p_model->GetEntityList()[i]->GetEntityType() == ENTITY_TYPES_ROCKET) {
			angle_rocket = p_model->GetEntityList()[i]->GetAngle();
			break;
		}
		else {

		}
	}

	for (INT32S i = 0; i < p_model->GetEntityList().size(); i++) {
		if (p_model->GetEntityList()[i]->GetEntityType() == ENTITY_TYPES_LIFE) {
			angle_littlelife = p_model->GetEntityList()[i]->GetAngle();
			break;
		}
		else {

		}
	}

	for (INT32S i = 0; i < p_model->GetEntityList().size(); i++) {
		if (p_model->GetEntityList()[i]->GetEntityType() == ENTITY_TYPES_BOMB) {
			angle_bomb = p_model->GetEntityList()[i]->GetAngle();
			break;
		}
		else {

		}
	}
}

void CalculateEntityVelocities()
{
	
	if (angle_orbitron_prev_time > angle_orbitron) {
		vel_orbitron = ((angle_orbitron + 360) - angle_orbitron_prev_time) / (game_clck - game_clck_prev);
	}
	else {
		vel_orbitron = (angle_orbitron - angle_orbitron_prev_time) / (game_clck - game_clck_prev);
	}

	if (angle_monster_prev_time > angle_monster) {
		vel_monster = ((angle_monster + 360) - angle_monster_prev_time) / (game_clck - game_clck_prev);
	}
	else {
		vel_monster = (angle_monster - angle_monster_prev_time) / (game_clck - game_clck_prev);
	}

	if (angle_rocket_prev_time > angle_rocket) {
		vel_rocket = ((angle_rocket + 360) - angle_rocket_prev_time) / (game_clck - game_clck_prev);
	}
	else {
		vel_rocket = (angle_rocket - angle_rocket_prev_time) / (game_clck - game_clck_prev);
	}

	if (angle_littlelife_prev_time > angle_littlelife) {
		vel_littlelife = ((angle_littlelife + 360) - angle_littlelife_prev_time) / (game_clck - game_clck_prev);
	}
	else {
		vel_littlelife = (angle_littlelife - angle_littlelife_prev_time) / (game_clck - game_clck_prev);
	}

	if (angle_bomb_prev_time > angle_bomb) {
		vel_bomb = ((angle_bomb + 360) - angle_bomb_prev_time) / (game_clck - game_clck_prev);
	}
	else {
		vel_bomb = (angle_bomb - angle_bomb_prev_time) / (game_clck - game_clck_prev);
	}

	game_clck_prev = game_clck;
	angle_orbitron_prev_time = angle_orbitron;
	angle_monster_prev_time = angle_monster;
	angle_rocket_prev_time = angle_rocket;
	angle_littlelife_prev_time = angle_littlelife;
	angle_bomb_prev_time = angle_bomb;
}

#endif