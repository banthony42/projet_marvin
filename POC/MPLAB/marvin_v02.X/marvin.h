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

#define ON 1
#define OFF 0

#define S_FOUND_YOU "Play sample of sound1"     // Exemple de message UART pour jouer un son ?
#define S_DONT_TALK "Play sample of sound2"     // sound1 / sound2 correspondront a un fichier dans la Pi
#define C_DESPERATE "Play behavior1"            // Exemple de message UART pour jouer un comportement ?
#define C_DONT_PANIC "Play behavior2"           // behavior1 / behavior2 correspondront a une fonction dans la Pi

/*
 *  REFRESH_PERIOD = temps de refresh des capteurs,
 *  TMR1 = Definition du temps donc, se baser sur une division de PR1 pour definir REFRESH_PERIOD ?
 */
#define REFRESH_PERIOD PR1 / x

void    marvin_init(m_marvin *marvin);
void    marvin_refresh(m_marvin *marvin);
u8      marvin_is_someone_left(m_marvin marvin);
u8      marvin_is_someone_right(m_marvin marvin);
u8      marvin_is_someone_found(m_marvin marvin);
void    marvin_stop_move(m_marvin *marvin);
void    marvin_turn_right(m_marvin *marvin);
void    marvin_turn_left(m_marvin *marvin);
void    marvin_eye(u8 state);
u32     get_time_sec(u32 timestamp, u32 nbr_periode);
u32     get_time_msec(u32 timestamp, u32 nbr_periode);

#endif	/* MARVIN_H */

