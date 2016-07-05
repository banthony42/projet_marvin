/* 
 * File:   Servo.h
 * Author: bocal
 *
 * Created on May 31, 2016, 6:03 PM
 */

#ifndef SERVO_H
#define	SERVO_H
#include "types.h"
#include "pwm.h"

#define PITCH_MIN 50
#define PITCH_MAX 100
#define YAW_MIN 10
#define YAW_MAX 170

void    marvin_attach_servo(m_servo *servo, u32 *pin ,u32 *ocrs, u16 min, u16 max, u8 oc_timer, u16 periode);
void    marvin_move_servo(m_servo *servo, s16 angle);
void    marvin_move_servo_speed(m_servo *servo, s16 angle, u16 deg_per_periode, u16 periode_msec);
void    marvin_move_to_position(u8 pitch_angle, u8 yaw_angle, u16 max_periode_msec);

#endif	/* SERVO_H */

