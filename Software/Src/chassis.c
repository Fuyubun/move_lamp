#include "main.h"
#include "chassis.h"
#include "chassis_config.h"//参数在这里改
#include "message.h"
#include "math.h"
#include "fytpi_math.h"
#include "tim.h"

#define COS60 0.5f
#define SIN60 0.86602540337844f

CHASSIS_T Chassis = {0};

CHASSIS_T* getChassisStruct(void)
{
	return (&Chassis);
}

//pid初始化
void CHASSIS_pidInit(void)
{
	for(uint8_t i=0;i<3;i++)
	{
		pidIncrementInit(&Chassis.mg310[i].pidIncrementSpeed,chassis_speed_kp,chassis_speed_ki,chassis_speed_kd,chassis_output_limit);
	}
}

//模式选择
void CHASSIS_modeChoose(void)
{
	switch(Chassis.mode)
	{
		case 0:
			CHASSIS_protect();
		break;
		case 1:
			break;
		case 2:
			CHASSIS_followMode();
		break;
	}
}

//运动学解算
/**
*    0
*  1   2
*/
void CHASSIS_kinematicSolution(void)
{
	Chassis.mg310[0].tar_speed = -Chassis.move_data.left                                           + Chassis.move_data.anticlockwise * chassis_radius * 0.4f;
	Chassis.mg310[1].tar_speed = +Chassis.move_data.left * COS60 + Chassis.move_data.front * SIN60 + Chassis.move_data.anticlockwise * chassis_radius * 0.4f;
	Chassis.mg310[2].tar_speed = +Chassis.move_data.left * COS60 - Chassis.move_data.front * SIN60 + Chassis.move_data.anticlockwise * chassis_radius * 0.4f;
}

//pid计算
void CHASSIS_pidCalculation(void)
{
	for(uint8_t i=0;i<3;i++)
	{
		Chassis.mg310[i].output = pidIncrementUpdate(Chassis.mg310[i].tar_speed,Chassis.mg310[i].speed,&Chassis.mg310[i].pidIncrementSpeed);
	}
}

//pwm发送
void CHASSIS_pwmTransimt(void)
{
	for(uint8_t i=0;i<3;i++)
	{
		Chassis.ccr[i] = absInt16(Chassis.mg310[i].output);
		int16_t dirction = sign(Chassis.mg310[i].output);
		MG310_sendPWM(i,dirction,Chassis.ccr[i]);
	}
}

//底盘保护
void CHASSIS_protect(void)
{
	Chassis.move_data.anticlockwise = 0;
	Chassis.move_data.front = 0;
	Chassis.move_data.left = 0;
	
	for(uint8_t i=0;i<3;i++)
	{
		Chassis.mg310[i].output = 0;
		Chassis.mg310[i].tar_speed = 0;
		Chassis.mg310[i].pidIncrementSpeed.err_now = 0;
		Chassis.mg310[i].pidIncrementSpeed.ctr_out = 0;
		Chassis.mg310[i].pidIncrementSpeed.d_ctr_out = 0;
		Chassis.mg310[i].pidIncrementSpeed.err_old_1 = 0;
		Chassis.mg310[i].pidIncrementSpeed.err_old_2 = 0;
		
		Chassis.ccr[i] = 0;
	}
}

void CHASSIS_process(void)
{
//	CHASSIS_modeChoose();
	CHASSIS_kinematicSolution();
	CHASSIS_pidCalculation();
}

//仅用于调试
void CHASSIS_blueToothMode(uint8_t rx_data)
{
	switch(rx_data)
	{
		case 0:
			Chassis.move_data.front = 0;
			Chassis.move_data.left = 0;
		break;
		case 1:
			Chassis.move_data.front = 50;
			Chassis.move_data.left = 0;
		break;
		case 2:
			Chassis.move_data.front = 50;
			Chassis.move_data.left = -50;
		break;
		case 3:
			Chassis.move_data.front = 0;
			Chassis.move_data.left = -50;
		break;
		case 4:
			Chassis.move_data.front = -50;
			Chassis.move_data.left = -50;
		break;
		case 5:
			Chassis.move_data.front = -50;
			Chassis.move_data.left = 0;
		break;
		case 6:
			Chassis.move_data.front = -50;
			Chassis.move_data.left = 50;
		break;
		case 7:
			Chassis.move_data.front = 0;
			Chassis.move_data.left = 50;
		break;
		case 8:
			Chassis.move_data.front = 50;
			Chassis.move_data.left = 50;
		break;
		case 9:
			Chassis.move_data.anticlockwise = 0;
		break;
		case 10:
			Chassis.move_data.anticlockwise = 1;
		break;
		case 11:
			Chassis.move_data.anticlockwise = -1;
		break;
	}
}

//跟随模式
void CHASSIS_followMode(void)
{
	Chassis.move_data.left = 0;
	Chassis.move_data.anticlockwise = 0;
	
	MESSAGE_T *message_temp = getMessageStruct();
	
	if(message_temp->bodyInduction_msg && message_temp->obstacle_distance > 200){
		Chassis.move_data.front = 40;
	}
	else
		CHASSIS_protect();
}
