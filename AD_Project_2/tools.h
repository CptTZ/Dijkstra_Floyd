/**
 * Tools for this project
 */

#pragma once

#include "common.h"

#include <time.h>


/**
 * Get a random integer with upper
 * @param upper Max
 * @return Rnd Int
 */
int nextRndInt(int upper);

/**
* Get Current Time Structure
* @return A time structure
*/
clock_t getCurrentClock();

/**
* Convert clock delta to ms
* @param stop End Time
* @param start Start Time
* @return delta in ms
*/
double clockToMs(const clock_t stop, const clock_t start);
