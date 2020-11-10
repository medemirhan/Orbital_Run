#pragma once

typedef unsigned char              BOOLEAN;
typedef unsigned char              INT8U;
typedef char                       INT8S;
typedef char                       CHAR;
typedef char*                      PCHAR;
typedef unsigned short             INT16U;
typedef short                      INT16S;
typedef unsigned int               INT32U;
typedef int                        INT32S;
typedef float                      FP32;
typedef long double                FP64;
typedef long long                  INT64S;
typedef unsigned long long         INT64U;

#define WINDOW_WIDTH                                 1200
#define WINDOW_HEIGHT                                900
#define WINDOW_CENTER_X                              WINDOW_WIDTH / 2.0f
#define WINDOW_CENTER_Y                              WINDOW_HEIGHT / 2.0f
#define INNER_ORBIT_RADIUS                           80.0f
#define DISTANCE_BTW_ORBITS                          57.0f
#define ENTITY_DRAWING_RADIUS                        10.0f
#define ENTITY_OUTLINE_THICKNESS                     2
#define ORBIT_POINT_COUNT                            200
#define BOUNDING_BOX_WIDTH                           ENTITY_DRAWING_RADIUS * 4.0f
#define BOUNDING_BOX_HEIGHT                          ENTITY_DRAWING_RADIUS * 4.0f
#define ORBITRON_INITIAL_ORBIT                       0
#define ENTITY_INITIAL_LIFE                          1
#define ENTITY_INITIAL_LITTLELIFE                    0
#define ENTITY_INITIAL_ROCKET_RIGHT                  0
#define SIN(x)                                       sin(x * 3.141592653589f / 180.0f)
#define COS(x)                                       cos(x * 3.141592653589f / 180.0f)
#define ATAN(x)                                      atan(x) * 180.0f / 3.141592653589f
#define ACOS(x)                                      acos(x) * 180.0f / 3.141592653589f
#define EUCLIDEAN_DIST(x1,x2,y1,y2)                  sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))
#define ANGLE_MAX                                    360.0f
#define ANGLE_MIN                                    0.0f
#define DIRECTION_IN                                 -1.0f
#define DIRECTION_OUT                                1.0f
#define DEFAULT_ROCKETRIGHT_VELOCITY                 0.0f
#define LOWER_LIMIT_ORBIT_NUM                        2
#define LOWER_LIMIT_MONSTER_NUM                      1
#define LOWER_LIMIT_ORBITRON_VEL                     0.1f
#define LOWER_LIMIT_MONSTER_VEL                      0.1f
#define UPPER_LIMIT_ORBIT_NUM                        7
#define UPPER_LIMIT_MONSTER_NUM                      30
#define UPPER_LIMIT_ORBITRON_VEL                     3.0f
#define UPPER_LIMIT_MONSTER_VEL                      3.0f
#define THREAD_SLEEP_TIME_MSEC                       10
#define LEVEL_DISPLAY_PRECISION                      3
#define MASK_ALPHA                                   150
#define VDEFAULT_ENTITTY_VBOMB_RATIO                 4.0f
#define VDEFAULT_ENTITTY_VLIFE_RATIO                 3.0f

typedef enum {
	ENTITY_TYPES_ORBITRON = 0,
	ENTITY_TYPES_MONSTER,
	ENTITY_TYPES_ROCKET,
	ENTITY_TYPES_ROCKET_RIGHT,
	ENTITY_TYPES_BOMB,
	ENTITY_TYPES_LIFE
}E_ENTITY_TYPES;

typedef enum {
	STATES_EXIT = -1,
	STATES_MAIN_MENU,
	STATES_CONFIG_MENU,
	STATES_PLAYING_SCREEN,
}E_STATES;

typedef enum {
	COLLISION_TYPES_ORBITRON_MONSTER = 0,
	COLLISION_TYPES_ORBITRON_BOMB,
	COLLISION_TYPES_ORBITRON_LIFE,
	COLLISION_TYPES_ORBITRON_ROCKETRIGHT,
	COLLISION_TYPES_MONSTER_ROCKET
}E_COLLISION_TYPES;