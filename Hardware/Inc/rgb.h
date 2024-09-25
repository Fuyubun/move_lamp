#ifndef __RGB_H__
#define __RGB_H__

#include "main.h"

/*CCR的宏定义*/
#define CODE_1       (67)       //1码定时器计数次数
#define CODE_0       (34)       //0码定时器计数次数

#define Pixel_NUM 64  //LED数量宏定义
 
/*建立一个定义单个LED三原色值大小的结构体*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;

extern const RGB_Color_TypeDef RED;   
extern const RGB_Color_TypeDef ORANGE;   
extern const RGB_Color_TypeDef YELLOW;   
extern const RGB_Color_TypeDef GREEN;
extern const RGB_Color_TypeDef CYAN;   
extern const RGB_Color_TypeDef BLUE;
extern const RGB_Color_TypeDef PURPLE;   
extern const RGB_Color_TypeDef WHITE;
extern const RGB_Color_TypeDef BLACK;

void RGB_setColorAndBrightness(const RGB_Color_TypeDef Color,uint8_t percent);
void RGB_solveData(uint8_t ledNumber);
void RGB_sendArray(void);         
void RGB_setParameter(uint8_t ledNumber,const RGB_Color_TypeDef Color,uint8_t brightness);
uint8_t RGB_autoBrightCalculate(const uint32_t envBright);
void RGB_refresh(void);

#endif /* __RGB_H__ */
