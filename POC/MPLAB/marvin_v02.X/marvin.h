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
#include "setup.h"
#include "Ir.h"
#include "leds.h"

#define ON 1
#define OFF 0

void    marvin_init(m_marvin *marvin);
void    marvin_refresh(m_marvin *marvin);
u8      marvin_is_someone_left(m_marvin marvin);
u8      marvin_is_someone_right(m_marvin marvin);
u8      marvin_is_someone_found(m_marvin marvin);
void    marvin_stop_move(m_marvin *marvin);
void    marvin_eye(u8 state);
u32     get_time_sec(u32 timestamp, u32 nbr_periode);
u32     get_time_msec(u32 timestamp, u32 nbr_periode);
void    marvin_behavior1();
void    marvin_behavior2();

#endif	/* MARVIN_H */

