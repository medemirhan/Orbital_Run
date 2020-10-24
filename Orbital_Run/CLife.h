#pragma once
#include "CEntity.h"

class CLife : public CEntity {
private:

public:
	CLife();
	CLife(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive);
	~CLife();
	void RotateEntity(FP32 x_pivot, FP32 y_pivot);
};