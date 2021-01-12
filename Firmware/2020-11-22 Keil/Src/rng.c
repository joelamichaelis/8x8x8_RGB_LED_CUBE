/*
 * rng.c
 *
 *  Created on: Jan 10, 2021
 *      Author: Joel Michaelis
 */
 
#include "rng.h"

uint32_t rngCount = 0;

/**
 * @brief produces a pseudo random number by taking the modulus of rngSeed by maxVal.
					note that this is only pseud random is rngSeed is a variable that changes with time.
 * @param[in] rngSeed - the seed which the modulus will happen to
 * @param[in] maxVal - the modulus operator/operand ?
 * @param[out] result - the resulting pseudo random number
 **/
uint32_t rand_32bit_modulus(uint32_t rngSeed, uint32_t maxVal)
{
	uint32_t result;
	result = (rngSeed % maxVal) + 1;
	return result;
}

uint64_t generate_random_color(uint32_t rngSeed)
{
	uint16_t redVal = rand_32bit_modulus(rngSeed, 4095);
	uint64_t retval = 0;
	return retval;
}
