#ifndef __CHASSIS_H__
#define __CHASSIS_H__

#include "main.h"
#include "fytpi_control.h"

typedef struct _MG310_T{
	float tar_speed;
	float speed;
	int16_t output;
	
	PID_INCREMENT_T pidIncrementSpeed;
}MG310_T;

typedef struct _MOVE_DATA_T{
	int16_t left;
	int16_t front;
	int16_t anticlockwise;
}MOVE_DATA_T;

typedef struct _CHASSIS_T{
	uint8_t mode;
	MG310_T mg310[3];
	MOVE_DATA_T move_data;
	uint16_t ccr[3];
}CHASSIS_T;

CHASSIS_T* getChassisStruct(void);
void CHASSIS_pidInit(void);
void CHASSIS_modeChoose(void);
void CHASSIS_kinematicSolution(void);
void CHASSIS_pidCalculation(void);
void CHASSIS_pwmTransimt(void);
void CHASSIS_protect(void);
void CHASSIS_process(void);
void CHASSIS_blueToothMode(uint8_t rx_data);
void CHASSIS_followMode(void);

#endif /* __CHASSIS_H__ */
