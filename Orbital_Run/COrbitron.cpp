#include "COrbitron.h"

COrbitron::COrbitron()
{

}

COrbitron::COrbitron(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive, INT32S num_little_life, INT32S num_rocket_right)
{
	Init(entity_type, pos_x, pos_y, velocity, radius, angle, orbit, num_life, is_alive, num_little_life, num_rocket_right);
}

COrbitron::~COrbitron()
{

}

void COrbitron::Init(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive, INT32S num_little_life, INT32S num_rocket_right)
{
	this->EntityType = entity_type;
	this->PositionX = pos_x;
	this->PositionY = pos_y;
	this->Velocity = velocity;
	this->Radius = radius;
	this->Angle = angle;
	this->Orbit = orbit;
	this->NumLife = num_life;
	this->IsAlive = is_alive;
	this->NumLittleLife = num_little_life;
	this->NumRocketRight = num_rocket_right;
}

void COrbitron::RotateEntity(FP32 x_pivot, FP32 y_pivot)
{
	FP32 x_shifted = this->PositionX - x_pivot;
	FP32 y_shifted = this->PositionY - y_pivot;

	this->PositionX = x_pivot + (x_shifted * COS(this->Velocity) - y_shifted * SIN(this->Velocity));
	this->PositionY = y_pivot + (x_shifted * SIN(this->Velocity) + y_shifted * COS(this->Velocity));
	this->Angle = fmod((this->Angle + this->Velocity), ANGLE_MAX);
}

void COrbitron::ChangeOrbit(FP32 direction)
{
	FP32 cur_pos_x = this->GetPositionX();
	FP32 cur_pos_y = this->GetPositionY();
	FP32 theta, updated_pos_x, updated_pos_y;

	if (cur_pos_x >= WINDOW_CENTER_X && cur_pos_y >= WINDOW_CENTER_Y) {
		theta = ATAN((cur_pos_y - WINDOW_CENTER_Y) / (cur_pos_x - WINDOW_CENTER_X));
	}
	else if (cur_pos_x < WINDOW_CENTER_X && cur_pos_y >= WINDOW_CENTER_Y) {
		theta = (ANGLE_MAX / 2.0f) + ATAN((cur_pos_y - WINDOW_CENTER_Y) / (cur_pos_x - WINDOW_CENTER_X));
	}
	else if (cur_pos_x < WINDOW_CENTER_X && cur_pos_y < WINDOW_CENTER_Y) {
		theta = (ANGLE_MAX / 2.0f) + ATAN((cur_pos_y - WINDOW_CENTER_Y) / (cur_pos_x - WINDOW_CENTER_X));
	}
	else if (cur_pos_x >= WINDOW_CENTER_X && cur_pos_y < WINDOW_CENTER_Y) {
		theta = ANGLE_MAX + ATAN((cur_pos_y - WINDOW_CENTER_Y) / (cur_pos_x - WINDOW_CENTER_X));
	}
	else {

	}
	updated_pos_x = (INNER_ORBIT_RADIUS + (this->GetOrbit() + direction) * DISTANCE_BTW_ORBITS) * COS(theta) + WINDOW_CENTER_X;
	updated_pos_y = (INNER_ORBIT_RADIUS + (this->GetOrbit() + direction) * DISTANCE_BTW_ORBITS) * SIN(theta) + WINDOW_CENTER_Y;
	this->SetPosition(updated_pos_x, updated_pos_y);
	this->Orbit = this->GetOrbit() + direction;
}

void COrbitron::SetNumLittleLife(INT32S num_little_life)
{
	this->NumLittleLife = num_little_life;
}

void COrbitron::SetNumRocketRight(INT32S num_rocket_right)
{
	this->NumRocketRight = num_rocket_right;
}

INT32S COrbitron::GetNumLittleLife() const
{
	return NumLittleLife;
}

INT32S COrbitron::GetNumRocketRight() const
{
	return NumRocketRight;
}
