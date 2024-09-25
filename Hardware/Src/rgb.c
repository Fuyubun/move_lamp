#include "main.h"
#include "tim.h"
#include "rgb.h"

/* 一些常见颜色的RGB值 */
const RGB_Color_TypeDef RED         = {255,0,0};   
const RGB_Color_TypeDef ORANGE      = {255,165,0};   
const RGB_Color_TypeDef YELLOW      = {255,255,0};   
const RGB_Color_TypeDef GREEN       = {0,255,0};
const RGB_Color_TypeDef CYAN        = {0,255,255};   
const RGB_Color_TypeDef BLUE        = {0,0,255};
const RGB_Color_TypeDef PURPLE      = {255,0,255};   
const RGB_Color_TypeDef WHITE       = {255,255,255};
const RGB_Color_TypeDef BLACK       = {0,0,0};

uint32_t Pixel_Buf[Pixel_NUM+1][24];       

//RGB缓存结构体
RGB_Color_TypeDef txColor = {0};

/* 设置颜色和亮度 */
void RGB_setColorAndBrightness(const RGB_Color_TypeDef Color,uint8_t percent)
{
	txColor.G = Color.G;
	txColor.R = Color.R;
	txColor.B = Color.B;
	
	txColor.G = txColor.G * percent / 100.0f;
	txColor.R = txColor.R * percent / 100.0f;
	txColor.B = txColor.B * percent / 100.0f;
}

/* 设置点亮灯的数量，将RGB值转化为发送数组的值 */
void RGB_solveData(uint8_t ledNumber)
{
	if(ledNumber > Pixel_NUM)
		return; //防止写入ID大于LED总数
	
	uint8_t i;
	for(uint8_t j = 0;j < ledNumber;j++){		
		for(i=0;i<8;i++) Pixel_Buf[j][i]   = ( (txColor.G & (1 << (7 -i)))? (CODE_1):CODE_0 );//数组某一行0~7转化存放G
		for(i=8;i<16;i++) Pixel_Buf[j][i]  = ( (txColor.R & (1 << (15-i)))? (CODE_1):CODE_0 );//数组某一行8~15转化存放R
		for(i=16;i<24;i++) Pixel_Buf[j][i] = ( (txColor.B & (1 << (23-i)))? (CODE_1):CODE_0 );//数组某一行16~23转化存放B
	}
	for(i=0;i<24;i++) Pixel_Buf[Pixel_NUM][i] = 0;
}

/* 封装一下上面两个函数，简洁一点 */
void RGB_setParameter(uint8_t ledNumber,const RGB_Color_TypeDef Color,uint8_t brightness)
{
	RGB_setColorAndBrightness(Color,brightness);
	RGB_solveData(ledNumber);
}

/* 自动亮度计算 */
uint8_t RGB_autoBrightCalculate(const uint32_t envBright)
{
	uint8_t percent;
	
	if(envBright < 1500)
		percent = 0;
	else
		percent = (envBright - 1500) * 100 / 1500.0f;
	
	percent = (percent > 100)?100:percent;//限幅
	
	return percent;
}

/* 发送数组，放在定时器中断中调用 */
void RGB_sendArray(void)
{  
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)Pixel_Buf,(Pixel_NUM+1)*24);
}

/* 清屏函数 */
void RGB_refresh(void)
{
	RGB_setParameter(Pixel_NUM,BLACK,0);
}
