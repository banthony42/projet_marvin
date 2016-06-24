
/*
 * Auteur : abary, amulin, banthony, tbelmaison
 * Debut Algo Final
 *
 */

#include "marvin.h"

int    main()
{
    // Code de test;
    u32 timestamp = 0;
    u32 nbr_periode = 0;
    u32 time = 0;
    LATFbits.LATF1 = 1;
    TRISFbits.TRISF1 = 0;
    TRISDbits.TRISD8 = 1;
    // Fin code de test;

    marvin_setup(&marvin);
    marvin_init(&marvin);
    while (1)
    {
        // Code de test;
        if (TMR1 == PR1 / 2)
        {
            LATFbits.LATF1 = !LATFbits.LATF1;
            timestamp = TMR1;
            nbr_periode = marvin.time->nbr_periode;
        }
        if (TMR1 == PR1)
        {
            time = get_time_sec(timestamp, nbr_periode);
            _nop();
        }
        // Fin code de test;

/*      if (TMR1 == REFRESH_PERIOD)
            marvin_refresh(&marvin);
        if (marvin_is_someone_right(marvin))
        {
            marvin_eye(OFF);
            marvin_turn_right(marvin);
        }
        if (marvin_is_someone_left(marvin))
        {
            marvin_eye(OFF);
            marvin_turn_left(marvin);
        }
        if (marvin_is_someone_found(marvin))
        {
            marvin_stop_move(marvin);
            marvin_eye(ON);
        }*/
    }
    return (0);
}