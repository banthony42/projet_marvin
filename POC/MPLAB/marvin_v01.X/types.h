/* 
 * File:   types.h
 * Author: bocal
 *
 * Created on May 31, 2016, 10:55 AM
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
 *  Structure de gestion du temps
 *  tmr = TMR1,
 *  nbr_cycle sera incremente via une interrupt
 *  est sera egale au nbr de fois ou la periode sera atteinte
 */
typedef struct  s_marvin_time
{
    u32     *tmr;
    u32     nbr_periode;
}               m_marvin_time;

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

typedef struct  s_sonar
{
    u8      echo_attachpin;     //Numeros de la PIN
    u8      trig_attachpin;     // Numeros de la PIN
    u32     *state_trig_pin;    // registre etat
    u32     *read_echo_pin;     // registre read
}               m_sonar;

#define SIZE_MESS 100           // Taille maximum d'un message UART

typedef struct      s_marvin
{
    m_marvin_time   *time;               // structure de gestion du temps
    m_servo         servo1;             // Objet servo1
    m_servo         servo2;             // Objet servo2
    m_servo         servo3;             // Objet servo3
    m_sonar         sonar1;             // Objet sonar1
    m_sonar         sonar2;             // Objet sonar2
    u16             val_sonar1;         // Valeur de mesure du sonar1
    u16             val_sonar2;         // Valeur de mesure du sonar2
    u16             val_ir;             // Valeur de mesure de l'IR
    u8              send[SIZE_MESS];    // Tableau pour l'envoi de message UART
    u8              receive[SIZE_MESS]; // Tableau pour la reception de message UART
    u16             counter1;           // Variable a tout faire ...
    u16             counter2;           // Varuable a tout faire ...
}                   m_marvin;

m_marvin_time time;
m_marvin marvin;


#endif	/* TYPES_H */

