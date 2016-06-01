/* 
 * File:   Servo.h
 * Author: bocal
 *
 * Created on May 31, 2016, 6:03 PM
 */

#ifndef SERVO_H
#define	SERVO_H
#include "types.h"

//Configure le PWM
#define MARVIN_OC1 &OC1CON
#define MARVIN_OC2 &OC2CON
#define MARVIN_OC3 &OC3CON
#define MARVIN_OC4 &OC4CON
#define MARVIN_OC5 &OC5CON

#define MARVIN_OC1R &OC1R
#define MARVIN_OC2R &OC2R
#define MARVIN_OC3R &OC3R
#define MARVIN_OC4R &OC4R
#define MARVIN_OC5R &OC5R

#define MARVIN_OC1RS &OC1RS
#define MARVIN_OC2RS &OC2RS
#define MARVIN_OC3RS &OC3RS
#define MARVIN_OC4RS &OC4RS
#define MARVIN_OC5RS &OC5RS

#define OC_ON 0b1 << 15     //OCx enabled
#define OC_OFF 0b0 << 15    //OCx disabled

#define OCM 0b110         //OutputCompare mode: PWM fault pin disabled

#define OC_TIMER3 1 << 3  // Sur OCTSEL TIMER3 is the clock source for this OutputCompare module
#define OC_TIMER2 0 << 3  // Sur OCTSEL TIMER2 is the clock source for this OutputCompare module

/*
 * Objet servo:
 * pin: pin a laquelle est attache le servo
 * min: duty_cycle minimum du servo en ms (ex: 500  (angle de 0deg))
 * max: duty_cycle maximum du servo en ms (ex: 2500 (angle de 180deg))
 * pos: derniere pos du servo en deg
 */

typedef struct  s_servo
{
    u32     *pin;
    u8      min;
    u8      max;
    u8      pos;
    u32     *ocrs;
}               m_servo;

void    marvin_attach_servo(m_servo *servo, u32 *pin, u32 *ocrs, u8 min, u8 max, u8 oc_timer);
void    marvin_moove_servo(m_servo *servo, u8 angle);

#endif	/* SERVO_H */

