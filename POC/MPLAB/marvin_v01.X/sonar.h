/* 
 * File:   sonar.h
 * Author: bocal
 *
 * Created on June 2, 2016, 7:01 PM
 */

#ifndef SONAR_H
#define	SONAR_H
#include "types.h"


typedef struct  s_sonar
{
    u32     trig_pin;
    u32     echo_pin;
}               m_sonar;

// fonction de setup
void    setup_sonar(m_sonar *sonar);

// fonctions de capture
void    marvin_trigger();
u16    marvin_pulseIN(); //Retourne Une seule capture
u16    marvin_capture();// retourne une distance en cm dedans on appelera le fonction de tri et la fonction de calcul de medianne
#endif	/* SONAR_H */

