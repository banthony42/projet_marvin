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

void    marvin_attach_servo(m_servo *servo, u32 *pin ,u32 *ocrs, u16 min, u16 max, u8 oc_timer, u16 periode);
void    marvin_move_servo(m_servo *servo, u8 angle);
void    marvin_move_servo_speed(m_servo *servo, u8 angle, u16 deg_per_periode, u16 periode_msec);

#endif	/* SERVO_H */

