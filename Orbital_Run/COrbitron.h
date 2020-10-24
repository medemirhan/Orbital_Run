#pragma once
#include "CEntity.h"

class COrbitron : public CEntity {
private:
	INT32S NumLittleLife;
	INT32S NumRocketRight;
public:
	COrbitron();
	COrbitron(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive, INT32S num_little_life, INT32S num_rocket_right);
	~COrbitron();
	void Init(E_ENTITY_TYPES entity_type, FP32 pos_x, FP32 pos_y, FP32 velocity, FP32 radius, FP32 angle, INT32S orbit, INT32S num_life, BOOLEAN is_alive, INT32S num_little_life, INT32S num_rocket_right);
	void RotateEntity(FP32 x_pivot, FP32 y_pivot);
	void ChangeOrbit(FP32 direction);
	void SetNumLittleLife(INT32S num_little_life);
	void SetNumRocketRight(INT32S num_rocket_right);
	INT32S GetNumLittleLife() const;
	INT32S GetNumRocketRight() const;
};

