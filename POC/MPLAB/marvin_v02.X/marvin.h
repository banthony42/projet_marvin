/*
 * File:   marvin.h
 * Author: bocal
 *
 * Created on June 16, 2016, 6:09 PM
 */

#ifndef MARVIN_H
#define	MARVIN_H

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "sonar.h"
#include "uart.h"
#include "tools.h"
#include "setup.h"
#include "Ir.h"
#include "leds.h"

#define ON 1
#define OFF 0

void    marvin_init(m_marvin *marvin);
void    marvin_refresh(m_marvin *marvin);
void    marvin_refresh_sensor(m_marvin *marvin);
u8      marvin_is_someone_left(m_marvin marvin);
u8      marvin_is_someone_right(m_marvin marvin);
u8      marvin_is_someone_found(m_marvin marvin);
void    marvin_stop_move(m_marvin *marvin);
void    marvin_eye(u8 state);
u32     get_time_sec(u32 timestamp, u32 nbr_periode);
u32     get_time_msec(u32 timestamp, u32 nbr_periode);
void    marvin_look_around();
void    marvin_spite();
void    marvin_pos_initial();
void    marvin_veille(u32 wait);
void    marvin_force_awaken();
void    marvin_eye_glow();
void    marvin_eye_blink();
u8      marvin_is_a_person();
void    marvin_reset_buffer();

#endif	/* MARVIN_H */

