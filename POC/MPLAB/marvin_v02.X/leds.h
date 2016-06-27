/*
 * File:   Servo.h
 * Author: bocal
 *
 * Created on May 31, 2016, 6:03 PM
 */

#ifndef LEDS_H
#define	LEDS_H
#include "types.h"
#include "pwm.h"

void    marvin_attach_led(m_led *led, u32 *pin ,u32 *ocrs, u16 min, u16 max, u8 oc_timer, u16 periode);
void    marvin_set_lux(m_led *led, s16 lux);
void    marvin_set_lux_speed(m_led *led, s16 lux, u16 deg_per_periode, u16 periode_msec);

#endif	/* LEDS_H */