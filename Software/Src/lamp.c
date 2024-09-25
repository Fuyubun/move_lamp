#include "main.h"
#include "tim.h"
#include "adc.h"
#include "lamp.h"

LAMP_T Lamp = {0};

LAMP_T* getLampStruct(void)
{
	return (&Lamp);
}

//���ݹ̶�ɫ�źŷ�����Ӧ����ɫ�ṹ��
RGB_Color_TypeDef LAMP_chooseFixedColor(uint8_t color_sign)
{
	RGB_Color_TypeDef rgb_temp;
	switch(color_sign)
	{
		case FIXED_RED:
			rgb_temp = RED;
		break;
		case FIXED_ORANGE:
			rgb_temp = ORANGE;
		break;
		case FIXED_YELLOW:
			rgb_temp = YELLOW;
		break;
		case FIXED_GREEN:
			rgb_temp = GREEN;
		break;
		case FIXED_CYAN:
			rgb_temp = CYAN;
		break;
		case FIXED_BLUE:
			rgb_temp = BLUE;
		break;
		case FIXED_PURPLE:
			rgb_temp = PURPLE;
		break;
		default:
			break;
	}
	return rgb_temp;
}

//�Զ�ģʽ
void LAMP_autoMode(void)
{
	if(Lamp.fixed_color != FIXED_NONE)
		Lamp.rgb = LAMP_chooseFixedColor(Lamp.fixed_color);
	
	Lamp.env_bright = adc_value[0];
	RGB_setParameter(Pixel_NUM,Lamp.rgb,RGB_autoBrightCalculate(Lamp.env_bright));
}

//�ֶ�ģʽ
void LAMP_handMode(void)
{
	//�̶�ɫ
	if(Lamp.fixed_color != FIXED_NONE){
		Lamp.rgb = LAMP_chooseFixedColor(Lamp.fixed_color);
		RGB_setParameter(Pixel_NUM,Lamp.rgb,Lamp.bright_hand);
	}
	//����RGBֵ
	else
		RGB_setParameter(Pixel_NUM,Lamp.rgb,100);	
}

//��Χģʽ
void LAMP_atmosphereMode(uint16_t now_time)
{
	//����������
	total_cycle = 0;
	for(uint8_t i=0;i<Lamp.atmo_color_num;i++)
	{
		total_cycle += (uint16_t)(Lamp.cycle[i]);
	}
	
	for(uint8_t i=0;i<Lamp.atmo_color_num;i++)
	{
		uint16_t time_temp = 0;
		//ȷ����ɫ
		Lamp.atmo_rgb[i] = LAMP_chooseFixedColor(Lamp.atmo_fixed_color[i]);
		//���ݵ�ǰʱ���ж��Ƿ�Ӧ�ø�����ɫ
		for(uint8_t j=0;j<i;j++){
			time_temp += Lamp.cycle[j];
		}
		if(now_time == time_temp)
			RGB_setParameter(Pixel_NUM,Lamp.atmo_rgb[i],100);
	}	
}

void LAMP_process(void)
{
//	static uint8_t last_mode = 0;

	//ģʽѡ��
	switch(Lamp.mode)
	{
		case LAMP_AUTO_MODE:
			LAMP_autoMode();
		break;
		case LAMP_HAND_MODE:
			LAMP_handMode();
		break;
//		case LAMP_ATMOSPHERE_MODE:
//			LAMP_atmosphereMode(now_time);
//		break;
		default:
			break;
	}
	
//	//ģʽ�л��ж�
//	if(last_mode == Lamp.mode)
//		lampModeShift_flag = 0;
//	else
//		lampModeShift_flag = (Lamp.mode == LAMP_ATMOSPHERE_MODE)?1:-1;
//	
//	last_mode = Lamp.mode;//�����ϴ�ģʽ
}

void LAMP_test(void)
{
	Lamp.mode = LAMP_HAND_MODE;
	Lamp.bright_hand = 70;
	Lamp.fixed_color = FIXED_ORANGE;
//	
//	Lamp.mode = LAMP_AUTO_MODE;
//	Lamp.fixed_color = FIXED_ORANGE;
}
