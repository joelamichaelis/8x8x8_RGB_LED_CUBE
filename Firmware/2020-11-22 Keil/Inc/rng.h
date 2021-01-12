/*
 * rng.h
 *
 *  Created on: Jan 10, 2021
 *      Author: Joel Michaelis
 */
 
#ifndef RNG_H_
#define RNG_H_

#include <stdint.h>

extern uint32_t rngCount;

/**
 * @brief produces a pseudo random number by taking the modulus of rngSeed by maxVal.
					note that this is only pseud random is rngSeed is a variable that changes with time.
 * @param[in] rngSeed - the seed which the modulus will happen to
 * @param[in] maxVal - the modulus operator/operand ?
 * @param[out] result - the resulting pseudo random number
 **/
uint32_t rand_32bit_modulus(uint32_t rngSeed, uint32_t maxVal);

#endif
