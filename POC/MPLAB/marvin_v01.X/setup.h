/* 
 * File:   setup.h
 * Author: bocal
 *
 * Created on June 16, 2016, 4:54 PM
 */

#ifndef SETUP_H
#define	SETUP_H

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "sonar.h"
#include "uart.h"

/*
 *  Structure de variables a declarer en global dans le main
 */
typedef struct  s_marvin
{
    m_servo     servo1;             // Objet servo1
    m_servo     servo2;             // Objet servo2
    m_servo     servo3;             // Objet servo3
    m_sonar     sonar1;             // Objet sonar1
    m_sonar     sonar2;             // Objet sonar2
    u16         val_sonar1;         // Valeur de mesure du sonar1
    u16         val_sonar2;         // Valeur de mesure du sonar2
    u16         val_ir;             // Valeur de mesure de l'IR
    u8          send[SIZE_MESS];    // Tableau pour l'envoi de message UART
    u8          receive[SIZE_MESS]; // Tableau pour la reception de message UART
    u16         counter1;           // Variable a tout faire ...
    u16         counter2;           // Varuable a tout faire ...
}               m_marvin;

void    marvin_setup();
void    marvin_setup_leds();
void    marvin_setup_timer();
void    marvin_setup_sonar();
void    marvin_setup_servo();
#endif	/* SETUP_H */

