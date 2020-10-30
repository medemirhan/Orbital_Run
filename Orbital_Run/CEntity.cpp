#include "CEntity.h"

CEntity::CEntity()
{

}

CEntity::CEntity(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive)
{
	Init(entity_type, pos_x, pos_y, velocity, radius, angle, orbit, num_life, is_alive);
}

CEntity::CEntity(const CEntity& entity)
{
	Init(entity.EntityType, entity.PositionX, entity.PositionX, entity.Velocity, entity.Radius, entity.Angle, entity.Orbit, entity.NumLife, entity.IsAlive);
}

CEntity::~CEntity()
{

}

/* Assigns values given as arguments to class members */
void CEntity::Init(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive)
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
}

void CEntity::SetEntityType(E_ENTITY_TYPES entity_type)
{
	this->EntityType = entity_type;
}

void CEntity::SetPosition(FP32 pos_x, FP32 pos_y)
{
	this->PositionX = pos_x;
	this->PositionY = pos_y;
}

void CEntity::SetVelocity(FP32 velocity)
{
	this->Velocity = velocity;
}

void CEntity::SetRadius(FP32 radius)
{
	this->Radius = radius;
}

void CEntity::SetAngle(FP32 angle)
{
	this->Angle = angle;
}

void CEntity::SetOrbit(INT32S orbit)
{
	this->Orbit = orbit;
}

void CEntity::SetNumLife(INT32S num_life)
{
	this->NumLife = num_life;
}

void CEntity::SetIsAlive(BOOLEAN is_alive)
{
	this->IsAlive = is_alive;
}

E_ENTITY_TYPES CEntity::GetEntityType() const
{
	return EntityType;
}

FP32 CEntity::GetPositionX() const
{
	return PositionX;
}

FP32 CEntity::GetPositionY() const
{
	return PositionY;
}

FP32 CEntity::GetVelocity() const
{
	return Velocity;
}

FP32 CEntity::GetRadius() const
{
	return Radius;
}

FP32 CEntity::GetAngle() const
{
	return Angle;
}

INT32S CEntity::GetOrbit() const
{
	return Orbit;
}

INT32S CEntity::GetNumLife() const
{
	return NumLife;
}

BOOLEAN CEntity::GetIsAlive() const
{
	return IsAlive;
}