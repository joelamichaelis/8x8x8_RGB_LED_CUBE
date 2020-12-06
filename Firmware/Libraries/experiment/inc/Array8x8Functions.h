/*
 * Array8x8Functions.h
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */
 
 
/**
 * @brief sets a single value within the array
 * @param[in] arrayPtr - points to the first element within the given array
 * @param[in] arrayIndex - specifies which element within the given array to be set
 * @param[in] value - the value which the given array element will be set to
 **/
void array_8x8_set_single(uint16_t *arrayPtr, int arrayIndex, uint16_t value);
 
 
/**
 * @brief sets array values iteratively with a for loop
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] startIndex - initial element in the aray to be set
 * @param[in] stepIndex - step size of the for loop
 * @param[in] stopIndex - final element in the aray to be set
 * @param[in] value - the value that all elements in the given loop will be set to
 **/
void array_8x8_set_multiple(uint16_t *arrayPtr, int startIndex, int stepIndex, int stopIndex, uint16_t value);

 
/**
 * @brief 
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] column - the column number of 0 through 7
 * @param[in] value - the value that all elements in the given column will be set to
 **/
void array_8x8_set_column(uint16_t *arrayPtr, int column, uint16_t value);
 
/**
 * @brief  shifts the 8x8 array right
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 **/
 void array_8x8_shift_right(uint16_t arrayPtr);
 
 
/**
 * @brief shifts the 8x8 array left
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 */
 void array_8x8_shift_left(uint16_t arrayPtr);
 
 /**
 * @brief shifts the 8x8 array forward
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 */
 void array_8x8_shift_forward(uint16_t arrayPtr);
 
/**
 * @brief shifts the 8x8 array back
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 */
void array_8x8_shift_back(uint16_t arrayPtr);