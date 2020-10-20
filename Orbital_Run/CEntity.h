#pragma once
#include <cmath>
#include "type_definitions.h"

class CEntity {
	friend class CModel;
protected:
	E_ENTITY_TYPES EntityType;
	FP32 PositionX;
	FP32 PositionY;
	FP32 Velocity;
	FP32 Radius;
	FP32 Angle;
	INT32S Orbit;
	INT32S NumLife;
	BOOLEAN IsAlive;

public:
	CEntity();
	CEntity(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive);
	CEntity(const CEntity& entity);
	~CEntity();
	virtual void RotateEntity(FP32 x_pivot, FP32 y_pivot) = 0;
	void Init(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive);
	void SetEntityType(E_ENTITY_TYPES entity_type);
	void SetPosition(FP32 pos_x, FP32 pos_y);
	void SetVelocity(FP32 velocity);
	void SetRadius(FP32 radius);
	void SetAngle(FP32 angle);
	void SetOrbit(INT32S orbit);
	void SetNumLife(INT32S num_life);
	void SetIsAlive(BOOLEAN is_alive);
	E_ENTITY_TYPES GetEntityType() const;
	FP32 GetPositionX() const;
	FP32 GetPositionY() const;
	FP32 GetVelocity() const;
	FP32 GetRadius() const;
	FP32 GetAngle() const;
	INT32S GetOrbit() const;
	INT32S GetNumLife() const;
	BOOLEAN GetIsAlive() const;
};