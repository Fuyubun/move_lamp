#ifndef __TOF_H__
#define __TOF_H__

#include "main.h"

extern uint8_t tof_dma_buf[5];

void Tof_Init(void);/* tof��ʼ������ */
void Get_TofData(void);/* ��ȡ����� */
void Tof_Conversion_HEX(uint8_t tof_dma_buf[],int *ptof);/* ���ݽ��㺯�� */

#endif /* __TOF_H__ */

