
#include <p32xxxx.h>
#include <sys/attribs.h>
#include "sonar.h"
#include "types.h"


// Ici on lui envoi LATxbits
void    marvin_trigger(u32 *pin)
{
    *pin = 1;
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    *pin = 0;
}

void    marvin_set_sonar(m_sonar *sonar, u32 trig_pin, u32 echo_pin)
{
    SONAR1_SET_TRIG = 0;
    SONAR1_SET_ECHO = 1;
    sonar->echo_pin = SONAR1_TRIG
}