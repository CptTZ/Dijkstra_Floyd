/**
 * Tools for this project
 */

#pragma once

#include "common.h"
#include <time.h>


/**
* \brief Get a random number with 1 - upper
* \param upper upperbound (inclusive)
* \return int
*/
int next_rnd_int(int upper);

/**
* \brief Get current CPU clock (For timing)
* \return clock_t
*/
clock_t get_current_clock();

/**
* \brief CPU clock delta to ms
* \param stop Stop Time
* \param start Start Time
* \return ms delta
*/
double clock_to_ms(const clock_t stop, const clock_t start);
