#include "timer.h"
#include "uart.h"

// refaire le check comme le timer pour avoir PBCLK

void    marvin_setup_baud_rate()
{
    // On seras tjrs en speed mode
   REGISTER_BAUD_RATE  = marvin_calcul_oscillator_prescaler() / (4 * BAUD_RATE) - 1;
}

// setup uart en speeed mode
void    marvin_setup_uart();
void    marvin_send_message();
void    marvin_receive_message();
