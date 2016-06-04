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
#define S2_ECHO_NPIN 8  // Numeros de PIN de l'ECHO

#define NBR_CAPTURE 11
typedef struct  s_sonar
{
    u8      echo_attachpin;
    u8      trig_attachpin;
    u32     *state_trig_pin;    // registre etat
    u32     *read_echo_pin;     // registre read
}               m_sonar;


void    marvin_set_sonar(m_sonar *sonar, u32 *trig_pin, u32 *trig_etat, u32 *echo_pin, u32 *echo_read);
void    marvin_trigger(m_sonar *sonar);
u16     marvin_pulseIn(m_sonar *sonar); //Retourne Une seule capture
u16     marvin_capture(m_sonar *sonar);// retourne une distance en cm dedans on appelera le fonction de tri et la fonction de calcul de medianne

#endif	/* SONAR_H */

