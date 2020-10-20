#include "CRocketRight.h"

CRocketRight::CRocketRight()
{

}

CRocketRight::CRocketRight(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive)
{
	Init(entity_type, pos_x, pos_y, velocity, radius, angle, orbit, num_life, is_alive);
}

CRocketRight::~CRocketRight()
{

}

void CRocketRight::RotateEntity(FP32 x_pivot, FP32 y_pivot)
{
	FP32 x_shifted = this->PositionX - x_pivot;
	FP32 y_shifted = this->PositionY - y_pivot;

	this->PositionX = x_pivot + (x_shifted * COS(this->Velocity) - y_shifted * SIN(this->Velocity));
	this->PositionY = y_pivot + (x_shifted * SIN(this->Velocity) + y_shifted * COS(this->Velocity));
	this->Angle = fmod((this->Angle + this->Velocity), ANGLE_MAX);
}