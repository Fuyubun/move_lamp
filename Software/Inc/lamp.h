#ifndef __LAMP_H__
#define __LAMP_H__

#include "main.h"
#include "rgb.h"

/* 灯模式宏定义 */
#define LAMP_AUTO_MODE       (0)  //自动模式，固定色选择，亮度随环境变化
#define LAMP_HAND_MODE       (1)  //手动模式，RGB值由用户自行设定或选择固定色
#define LAMP_ATMOSPHERE_MODE (2)  //氛围模式，几种颜色交替闪，闪的颜色可自选RGB值或选择固定色（上限为7种），闪的时间自行设定（1s~1min）

/* 固定色信号宏定义 */
#define FIXED_NONE    (0)  //自由RGB值
#define FIXED_RED     (1)  //红
#define FIXED_ORANGE  (2)  //橙
#define FIXED_YELLOW  (3)  //黄
#define FIXED_GREEN   (4)  //绿
#define FIXED_CYAN    (5)  //青
#define FIXED_BLUE    (6)  //蓝
#define FIXED_PURPLE  (7)  //紫

typedef struct _LAMP_T{
	uint8_t mode;//灯的模式
	uint32_t env_bright;//环境亮度
	
	uint8_t bright_hand;//手动模式下固定色的亮度
	uint8_t fixed_color;//自动和手动模式下的固定色信号
	RGB_Color_TypeDef rgb;//自动和手动模式下的颜色结构体
	
	uint8_t atmo_color_num;//氛围模式下选择的颜色数量
	uint8_t atmo_fixed_color[7];//氛围模式下的固定色信号
	RGB_Color_TypeDef atmo_rgb[7];//氛围模式下的颜色结构体
	uint8_t cycle[7];//氛围模式下闪烁周期
}LAMP_T;

LAMP_T* getLampStruct(void);
RGB_Color_TypeDef LAMP_chooseFixedColor(uint8_t color_sign);
void LAMP_autoMode(void);
void LAMP_handMode(void);
void LAMP_atmosphereMode(uint16_t now_time);
void LAMP_process(void);
void LAMP_test(void);

#endif /* __LAMP_H__ */
