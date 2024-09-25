#include "main.h"
#include "adc.h"
#include "tof.h"
#include "lamp.h"
#include "chassis.h"
#include "message.h"

MESSAGE_T Message = {0};

MESSAGE_T* getMessageStruct(void)
{
	return (&Message);
}

void MESSAGE_dataProcess(void)
{
	Message.bodyInduction_msg = (adc_value[1]>3449)?1:0;
	Tof_Conversion_HEX(tof_dma_buf,&Message.obstacle_distance);
}

//上位机控制
void MESSAGE_upperComputerControl(const uint8_t uart_buf[],LAMP_T *lamp,CHASSIS_T *chassis)
{
	if(uart_buf[0] == 0xAA && uart_buf[38] == 0xBB){
		lamp->mode = uart_buf[1];
		switch(lamp->mode)
		{
			case 0://自动
				lamp->fixed_color = uart_buf[3];
			break;
			case 1://手动
				lamp->fixed_color = uart_buf[3];
				lamp->bright_hand = uart_buf[2];
				lamp->rgb.R = uart_buf[10];
				lamp->rgb.R = uart_buf[11];
				lamp->rgb.R = uart_buf[12];
			break;
//			case 2:
//				lamp->atmo_color_num = uart_buf[2];
//				if(lamp->atmo_color_num > 7)
//					break;
//				for(uint8_t i=0;i<lamp->atmo_color_num;i++){
//					lamp->atmo_fixed_color[i] = uart_buf[i + 3];
//					lamp->atmo_rgb[i].R = uart_buf[i*3 + 10];
//					lamp->atmo_rgb[i].G = uart_buf[i*3 + 11];
//					lamp->atmo_rgb[i].B = uart_buf[i*3 + 12];
//					lamp->cycle[i] = uart_buf[i + 31];
//				}
//			break;
		}
	}
	
	if(uart_buf[39] == 0xCC && uart_buf[44] == 0xDD){
		chassis->mode = uart_buf[40];
		if(chassis->mode == 1){
			switch(uart_buf[41])
			{
				case 0:
					chassis->move_data.left = 0;
				break;
				case 1:
					chassis->move_data.left = 50;
				break;
				case 2:
					chassis->move_data.left = -50;
				break;
			}
			switch(uart_buf[42])
			{
				case 0:
					chassis->move_data.front = 0;
				break;
				case 1:
					chassis->move_data.front = 50;
				break;
				case 2:
					chassis->move_data.front = -50;
				break;
			}
			switch(uart_buf[43])
			{
				case 0:
					chassis->move_data.anticlockwise = 0;
				break;
				case 1:
					chassis->move_data.anticlockwise = -1;
				break;
				case 2:
					chassis->move_data.anticlockwise = 1;
				break;
			}
		}
	}
}
