
/*
 * Auteur : abary, amulin, banthony, tbelmaison
 * Debut Algo Final
 *
 */

#include "marvin.h"

/*
 * Declaration de la structure de variable globale
 */
m_marvin marvin;

int    main()
{
    marvin_setup(&marvin);
    marvin_init(&marvin);
    while (1)
    {
        if (TMR1 == REFRESH_PERIOD)
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
        }
    }
    return (0);
}