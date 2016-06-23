/* 
 * File:   types.h
 * Author: bocal
 *
 * Created on June 22, 2016, 6:33 PM
 */

#ifndef TYPES_H
#define	TYPES_H


#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long
// Un define sur vloatile unsigned int pour les warning???
#define s8 signed char
#define s16 signed short
#define s32 signed long


/*
 * Objet servo:
 * pin: pin a laquelle est attache le servo
 * min: duty_cycle minimum du servo en ms (ex: 500  (angle de 0deg))
 * max: duty_cycle maximum du servo en ms (ex: 2500 (angle de 180deg))
 * pos: derniere pos du servo en deg
 * ocrs: registre de control correspondant a la PIN du servo
 * periode: periode du servo pour le signal PWM
 * oc_timer: registre cde comparaison secondaire correspondant a la PIN du servo
 * incr: Valeur d'increment de position (pas encore utilise)
 */

typedef struct  s_servo
{
    u32     *pin;
    u16      min;
    u16      max;
    u8      pos;
    u32     *ocrs;
    u16     periode;
    u8      oc_timer;
    s8      incr;
}               m_servo;

#endif	/* TYPES_H */

