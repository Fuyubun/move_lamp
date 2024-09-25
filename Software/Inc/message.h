#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "main.h"
#include "lamp.h"
#include "chassis.h"

typedef struct _MESSAGE_T{
	uint8_t bodyInduction_msg;
	uint8_t chassis_test_uart_buf;
	int obstacle_distance;
}MESSAGE_T;

MESSAGE_T* getMessageStruct(void);
void MESSAGE_dataProcess(void);
void MESSAGE_upperComputerControl(const uint8_t uart_buf[],LAMP_T *lamp,CHASSIS_T *chassis);

#endif /* __MESSAGE_H__ */
