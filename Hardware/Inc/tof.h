#ifndef __TOF_H__
#define __TOF_H__

#include "main.h"

extern uint8_t tof_dma_buf[5];

void Tof_Init(void);/* tof初始化函数 */
void Get_TofData(void);/* 读取命令函数 */
void Tof_Conversion_HEX(uint8_t tof_dma_buf[],int *ptof);/* 数据解算函数 */

#endif /* __TOF_H__ */

