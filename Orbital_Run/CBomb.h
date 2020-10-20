#pragma once
#include "CEntity.h"

class CBomb : public CEntity
{
private:

public:
	CBomb();
	CBomb(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive);
	~CBomb();
	void RotateEntity(FP32 x_pivot, FP32 y_pivot);
};