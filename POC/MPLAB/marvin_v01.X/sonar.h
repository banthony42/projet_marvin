/* 
 * File:   sonar.h
 * Author: bocal
 *
 * Created on June 2, 2016, 7:01 PM
 */

#ifndef SONAR_H
#define	SONAR_H
#include "types.h"

#define SONAR1_SET_TRIG &TRISE  // Adresse du REGISTRE TRIG (TRISx)
#define SONAR1_STATE_TRIG &LATE // Adresse du REGISTRE SET TRIG (LATx)
#define SONAR1_SET_ECHO &TRISD  // Adresse du REGISTRE ECHO (TRISx)
#define SONAR1_READ_ECHO &PORTD // Adresse du REGISTRE LECTURE ECHO (PORTx)

#define S1_TRIG_NPIN 0  // Numeros de PIN du TRIGGER
#define S1_ECHO_NPIN 9  // Numeros de PIN de l'ECHO

#define S2_TRIG_NPIN 1  // Numeros de PIN du TRIGGER
#define S2_ECHO_NPIN 7  // Numeros de PIN de l'ECHO

#define NBR_CAPTURE 11



void    marvin_set_sonar(m_sonar *sonar, u32 *trig_pin, u32 *trig_etat, u32 *echo_pin, u32 *echo_read);
void    marvin_trigger(m_sonar *sonar);
u16     marvin_pulseIn(m_sonar *sonar);
u16     marvin_capture(m_sonar *sonar);

#endif	/* SONAR_H */

