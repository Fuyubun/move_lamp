#ifndef __CHASSIS_CONFIG_H__
#define __CHASSIS_CONFIG_H__

/* 底盘pid参数 */
float chassis_speed_kp = 7.0f;
float chassis_speed_ki = 0.0f;
float chassis_speed_kd = 0.0f;

/* 限幅 */
float chassis_output_limit = 1000.0f;

/* 底盘相关物理参数 */
float wheel_radius = 28.5f;//轮子半径，单位:mm
float chassis_radius = 100.0f;//底盘半径，单位:mm

#endif /* __CHASSIS_CONFIG_H__ */
