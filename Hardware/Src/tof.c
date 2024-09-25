#include "main.h"
#include "usart.h"
#include "tof.h"

uint8_t tof_dma_buf[5] = {0};//��������,asciiֵ

/* tof��ʼ������ */
void Tof_Init(void)
{
	/* ����tof��� */
//	Send_Data_To_UART('s');
//	Send_Data_To_UART('7');
//	Send_Data_To_UART('-');
//	Send_Data_To_UART('1');
//	Send_Data_To_UART('#');
	
	/* ��ÿ��20�ε��ٶ�̽�� */
	Send_Data_To_UART('s');
	Send_Data_To_UART('2');
	Send_Data_To_UART('-');
	Send_Data_To_UART('1');
	Send_Data_To_UART('0');
	Send_Data_To_UART('#');
	
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3,tof_dma_buf,sizeof(tof_dma_buf));
    __HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);
}

/* ��ȡ����� */
void Get_TofData(void)
{
	/* ��ȡһ�ξ��� */
	Send_Data_To_UART('r');
	Send_Data_To_UART('6');
	Send_Data_To_UART('#');
}

/* ���ݽ��㺯�� */
void Tof_Conversion_HEX(uint8_t tof_dma_buf[],int *ptof)
{
	int value_num=0;
	for(int i=0;i<5;i++)
	{     
			if(tof_dma_buf[i]!='\r'&&tof_dma_buf[i]!='\n')
			value_num++;//λ��
	}
	switch(value_num)
	{
		case 1://һλ��
			for(int i_1=0;i_1<5;i_1++)
			{
				if(tof_dma_buf[i_1]!='\r'&&tof_dma_buf[i_1]!='\n')
					*ptof=(tof_dma_buf[i_1]*1-'0');
			}
			break;
		case 2://��λ��
			for(int i_2=0;i_2<5;i_2++)
			{
				if(tof_dma_buf[i_2]=='\r'&&i_2>=2)
					*ptof=((tof_dma_buf[i_2-2]-'0')*10)+((tof_dma_buf[i_2-1]-'0')*1);
				else if(tof_dma_buf[1]=='\r')
				*ptof=((tof_dma_buf[4]-'0')*10)+((tof_dma_buf[0]-'0')*1);
				else if(tof_dma_buf[0]=='\r')
				*ptof=((tof_dma_buf[3]-'0')*10)+((tof_dma_buf[4]-'0')*1);
			}
			break;
		case 3://��λ��
			for(int i_3=0;i_3<5;i_3++)
			{
				if(tof_dma_buf[i_3]=='\r'&&i_3>=3)
				{
					*ptof=((tof_dma_buf[i_3-3]-'0')*100)+((tof_dma_buf[i_3-2]-'0')*10)+((tof_dma_buf[i_3-1]-'0')*1);
				}
				else if(tof_dma_buf[2]=='\r')
					*ptof=((tof_dma_buf[4]-'0')*100)+((tof_dma_buf[0]-'0')*10)+((tof_dma_buf[1]-'0')*1);
				else if(tof_dma_buf[1]=='\r')
					*ptof=((tof_dma_buf[3]-'0')*100)+((tof_dma_buf[4]-'0')*10)+((tof_dma_buf[0]-'0')*1);
				else if(tof_dma_buf[0]=='\r')
					*ptof=((tof_dma_buf[2]-'0')*100)+((tof_dma_buf[3]-'0')*10)+((tof_dma_buf[4]-'0')*1);
			}
			break;
	}
}
