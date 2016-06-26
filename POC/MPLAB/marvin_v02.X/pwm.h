/* 
 * File:   pwm.h
 * Author: bocal
 *
 * Created on June 26, 2016, 6:20 PM
 */

#ifndef PWM_H
#define	PWM_H

/*
 *  Registres de controle des differentes sorties OutputCompare
 */
#define MARVIN_OC1 &OC1CON
#define MARVIN_OC2 &OC2CON
#define MARVIN_OC3 &OC3CON
#define MARVIN_OC4 &OC4CON
#define MARVIN_OC5 &OC5CON

/*
 *  Registres de comparaison des differentes sorties OutputCompare
 */
#define MARVIN_OC1R &OC1R
#define MARVIN_OC2R &OC2R
#define MARVIN_OC3R &OC3R
#define MARVIN_OC4R &OC4R
#define MARVIN_OC5R &OC5R

/*
 *  Registres de comparaison secondaire des differentes sorties OutputCompare
 */
#define MARVIN_OC1RS &OC1RS
#define MARVIN_OC2RS &OC2RS
#define MARVIN_OC3RS &OC3RS
#define MARVIN_OC4RS &OC4RS
#define MARVIN_OC5RS &OC5RS

#define OC_ON 1 << 15       //OCx enabled
#define OC_OFF 0 << 15      //OCx disabled

#define OCM 0b110           //OutputCompare mode: PWM fault pin disabled

#define OC_TIMER3 1 << 3    // Sur OCTSEL TIMER3 is the clock source for this OutputCompare module
#define OC_TIMER2 0 << 3    // Sur OCTSEL TIMER2 is the clock source for this OutputCompare module

#endif	/* PWM_H */

