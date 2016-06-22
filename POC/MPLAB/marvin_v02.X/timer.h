/*
 * File:   timer.h
 * Author: bocal
 *
 * Created on May 31, 2016, 6:03 PM
 */

#ifndef TIMER_H
#define	TIMER_H
#include "types.h"


/*
 * Registre pour sets les timers
 */

#define MARVIN_CONF_TIMER1 &T1CON
#define MARVIN_CONF_TIMER2 &T2CON
#define MARVIN_CONF_TIMER3 &T3CON
#define MARVIN_CONF_TIMER4 &T4CON

/*
 * Registre des TIMERS
 */
#define MARVIN_TIMER1 &TMR1
#define MARVIN_TIMER2 &TMR2
#define MARVIN_TIMER3 &TMR3
#define MARVIN_TIMER4 &TMR4

/*
 * Registre pour definir la periode des timers
 */

#define MARVIN_PR1 &PR1
#define MARVIN_PR2 &PR2
#define MARVIN_PR3 &PR3
#define MARVIN_PR4 &PR4

// set le timer
#define TIMER_ON 0b1 << 15
#define TIMER_OFF 0b0

// set GATE bits 7
#define TIMER_GATE_ON 0b1 << 7
#define TIMER_GATE_OFF 0b0

// set tckps bits 4-5  TYPEA
#define TCKPS00 0b0
#define TCKPS01 0b1 << 4
#define TCKPS10 0b10 << 4
#define TCKPS11 0b11 << 4

// set tckps bits 4-6  TYPEB
#define TCKPS000 0b0 << 4
#define TCKPS001 0b1 << 4
#define TCKPS010 0b10 << 4
#define TCKPS011 0b11 << 4
#define TCKPS100 0b100 << 4
#define TCKPS101 0b101 << 4
#define TCKPS110 0b110 << 4
#define TCKPS111 0b111 << 4

// valeur de losc interne en Hertz
#define OCSINTERNE 8000000
#define OSC_INTERNE OSCCON
#define TIME_SEC 1
#define TIME_MSEC 1000
#define TIME_MICS 1000000

#define TYPE_A 1
#define TYPE_B 0


void    marvin_set_timer(u32 *stimer, u8 prescale, u8 gate, u32 *timer);
void    marvin_set_periode(u32 *pr_timer, u16 periode, u8 types, u32 *conf_tmr, u16 unit);
u32     marvin_calcul_oscillator_prescaler();

#endif	/* TIMER_H */
