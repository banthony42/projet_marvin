/*
 * File:   sonar.h
 * Author: bocal
 *
 * Created on June 2, 2016, 7:01 PM
 */

#ifndef SONAR_H
#define	SONAR_H
#include "types.h"

#define SONAR_SET_TRIG &TRISA  // Adresse du REGISTRE TRIG (TRISx)
#define SONAR_STATE_TRIG &LATA // Adresse du REGISTRE SET TRIG (LATx)
#define SONAR_SET_ECHO &TRISB  // Adresse du REGISTRE ECHO (TRISx)
#define SONAR_READ_ECHO &PORTB // Adresse du REGISTRE LECTURE ECHO (PORTx)

#define S1_TRIG_NPIN 3  // Numeros de PIN du TRIGGER S1
#define S1_ECHO_NPIN 8  // Numeros de PIN de l'ECHO S1

#define S2_TRIG_NPIN 2  // Numeros de PIN du TRIGGER S2
#define S2_ECHO_NPIN 7  // Numeros de PIN de l'ECHO S2

#define NBR_CAPTURE 5



void    marvin_set_sonar(m_sonar *sonar, u32 *trig_pin, u32 *trig_etat, u32 *echo_pin, u32 *echo_read);
void    marvin_trigger(m_sonar *sonar);
u16     marvin_pulseIn(m_sonar *sonar);
u16     marvin_capture(m_sonar *sonar);

#endif	/* SONAR_H */