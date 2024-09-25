#ifndef __CHASSIS_CONFIG_H__
#define __CHASSIS_CONFIG_H__

/* ����pid���� */
float chassis_speed_kp = 7.0f;
float chassis_speed_ki = 0.0f;
float chassis_speed_kd = 0.0f;

/* �޷� */
float chassis_output_limit = 1000.0f;

/* �������������� */
float wheel_radius = 28.5f;//���Ӱ뾶����λ:mm
float chassis_radius = 100.0f;//���̰뾶����λ:mm

#endif /* __CHASSIS_CONFIG_H__ */
