#ifndef __LAMP_H__
#define __LAMP_H__

#include "main.h"
#include "rgb.h"

/* ��ģʽ�궨�� */
#define LAMP_AUTO_MODE       (0)  //�Զ�ģʽ���̶�ɫѡ�������滷���仯
#define LAMP_HAND_MODE       (1)  //�ֶ�ģʽ��RGBֵ���û������趨��ѡ��̶�ɫ
#define LAMP_ATMOSPHERE_MODE (2)  //��Χģʽ��������ɫ��������������ɫ����ѡRGBֵ��ѡ��̶�ɫ������Ϊ7�֣�������ʱ�������趨��1s~1min��

/* �̶�ɫ�źź궨�� */
#define FIXED_NONE    (0)  //����RGBֵ
#define FIXED_RED     (1)  //��
#define FIXED_ORANGE  (2)  //��
#define FIXED_YELLOW  (3)  //��
#define FIXED_GREEN   (4)  //��
#define FIXED_CYAN    (5)  //��
#define FIXED_BLUE    (6)  //��
#define FIXED_PURPLE  (7)  //��

typedef struct _LAMP_T{
	uint8_t mode;//�Ƶ�ģʽ
	uint32_t env_bright;//��������
	
	uint8_t bright_hand;//�ֶ�ģʽ�¹̶�ɫ������
	uint8_t fixed_color;//�Զ����ֶ�ģʽ�µĹ̶�ɫ�ź�
	RGB_Color_TypeDef rgb;//�Զ����ֶ�ģʽ�µ���ɫ�ṹ��
	
	uint8_t atmo_color_num;//��Χģʽ��ѡ�����ɫ����
	uint8_t atmo_fixed_color[7];//��Χģʽ�µĹ̶�ɫ�ź�
	RGB_Color_TypeDef atmo_rgb[7];//��Χģʽ�µ���ɫ�ṹ��
	uint8_t cycle[7];//��Χģʽ����˸����
}LAMP_T;

LAMP_T* getLampStruct(void);
RGB_Color_TypeDef LAMP_chooseFixedColor(uint8_t color_sign);
void LAMP_autoMode(void);
void LAMP_handMode(void);
void LAMP_atmosphereMode(uint16_t now_time);
void LAMP_process(void);
void LAMP_test(void);

#endif /* __LAMP_H__ */
