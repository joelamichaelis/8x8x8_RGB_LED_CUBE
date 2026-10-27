/*
 * array_8x8.h
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */
 
 
#ifndef ARRAY_8X8
#define ARRAY_8X8

// An alternate enum implementation style?
// up and down are out of scope since they're the 3rd dimension and this is a 2D library
#define DIRECTION_CW 			1 
#define DIRECTION_CCW 		2
#define DIRECTION_RIGHT 	3
#define DIRECTION_LEFT 		4
#define DIRECTION_FORWARD 5
#define DIRECTION_BACK	  6
#define DIRECTION_INWARD	7 //"implode"
#define DIRECTION_OUTWARD	8 //"explode"
#define DIRECTION_IN			9		//"transition in"
#define DIRECTION_OUT			10	//"transition out

//#define DIRECTION_UP		  11
//#define DIRECTION_DOWN	  12

#define MAX_BRIGHTNESS 4095

#include "rng.h"

//--------------------------------------------------SET FUNCTIONS BEGIN---------------------------------------------------------//

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
 * @brief sets a section of a column #colNum which starts at startRowNum and stops at stopRowNum to value
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] colNum: the column which is having a section set bounded between 0 & 7
 * @param[in] startRowNum: a projection, bounded between 0 & 7
 * @param[in] stopRowNum: a projection, bounded between 0 & 7
 * @param[in] value - the value that all elements in the given row segment will be set to
 **/
void array_8x8_set_col_segment(uint16_t *arrayPtr, uint8_t colNum, uint8_t startRowNum, uint8_t stopRowNum, uint16_t value);

/**
 * @brief 
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] row - the row number of 0 through 7
 * @param[in] value - the value that all elements in the given row will be set to
 **/
void array_8x8_set_row(uint16_t *arrayPtr, int row, uint16_t value);

/**
 * @brief sets a section of a row #rowNum which starts at startColNum and stops at stopColNum to value
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] rowNum - the row which is having a section set, bounded between 0 & 7
 * @param[in] startColNum - a projection, bounded between 0 & 7
 * @param[in] stopColNum - a projection, bounded between 0 & 7
 * @param[in] value - the value that all elements in the given row segment will be set to
 **/
void array_8x8_set_row_segment(uint16_t *arrayPtr, uint8_t rowNum, uint8_t startColNum, uint8_t stopColNum, uint16_t value);

/**
 * @brief Creates a "wireframe" square in the array by setting all elements to value. startPt and stopPt are opposite corners.
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] value - the value that all elements in the given row segment will be set to
 * @param[in] startPt - one corner of the square
 * @param[in] stopPt - the opposing corner of the square
 **/
void array_8x8_set_square(uint16_t *arrayPtr, uint16_t value, uint8_t startPt, uint8_t stopPt);

//----------------------------------------------------SET FUNCTIONS END---------------------------------------------------------//

//-----------------------------------------------MODIFY FUNCTIONS BEGIN---------------------------------------------------------//

/**
 * @brief  shifts the 8x8 array in the specified direction.
 *				 zeros are shifted in where applicable
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 **/
 void array_8x8_shift(uint16_t *arrayPtr, uint8_t direction);
 
/**
 * @brief  shifts the 8x8 array in the specified direction and wraps around. zeros aren't shifted in.
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 **/
 void array_8x8_rotate(uint16_t *arrayPtr, uint8_t direction); 
 
/**
 * @brief  inverts all elements of the array by subtracting the original value from the max possible value
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 **/
 void array_8x8_invert(uint16_t *arrayPtr); 

//----------------INTUITIVE FULL ARRAY FUNCTIONS END----------------------------------------//

//--------------------------PARTIAL ARRAY SHIFT & ROTATE FUNCTIONS BEGIN-------------------------//
/**
 * @brief shifts a column of the 8x8 array in a specified direction. a zero is shifted in
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] colNum - indicates which column is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 */
void array_8x8_shift_column(uint16_t *arrayPtr, uint8_t colNum, uint8_t direction);

/**
 * @brief shifts a column of the 8x8 array in a specified direction and wraps around
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] colNum - indicates which column is to be rotated (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 */
void array_8x8_rotate_column(uint16_t *arrayPtr, uint8_t colNum, uint8_t direction);

/**
 * @brief shifts the 8x8 array forward
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] rowNum - indicates which row is to be shifted (0 - 7)
 * @param[in] direction - the desired shift direction
 */
void array_8x8_shift_row(uint16_t *arrayPtr, uint8_t rowNum, uint8_t direction);

/**
 * @brief shifts a row of the 8x8 array in a specified direction and wraps around
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] rowNum - indicates which row is to be rotated (0 - 7)
 * @param[in] direction - the desired shift direction
 */
void array_8x8_rotate_row(uint16_t *arrayPtr, uint8_t rowNum, uint8_t direction);

//--------------------------PARTIAL ARRAY SHIFT & ROTATE FUNCTIONS END---------------------------//


//-------------------------------QUADRANT CORNER FUNTIONS BEGIN----------------------------------//

/**
 * @brief rotates the 8x8 array quadrants' outside 2x2 corners counter-clockwise
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 */
void array_8x8_quadrant_corner_rotate_ccw(uint16_t *arrayPtr);

//-------------------------------QUADRANT CORNER FUNTIONS END------------------------------------//

//-------------------------------RING ROTATE FUNTIONS BEGIN--------------------------------------//

/**
 * @brief refers to the outermost (8x8) box or ring of LEDs in the 8x8 array. 
 *				the pixels are all shifted by a 1-pixel offset in a counter-clockwise circular manner.
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - determines whether the operation will be clockwise or counter-clockwise
 */
void array_8x8_ring_8x8_rotate(uint16_t *arrayPtr, uint8_t direction);

/**
 * @brief refers to the second from outermost (6x6) box or ring of LEDs in the 8x8 array. 
 *				the pixels are all shifted by a 1-pixel offset in a counter-clockwise circular manner.
 *				performing this operation 28x in succession will result in the original array.
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - determines whether the operation will be clockwise or counter-clockwise
 */
void array_8x8_ring_6x6_rotate(uint16_t *arrayPtr, uint8_t direction);

/**
 * @brief refers to the second from innermost (4x4) box or ring of LEDs in the 8x8 array. 
 *				the pixels are all shifted by a 1-pixel offset in a counter-clockwise circular manner.
 *				performing this operation 12x in succession will result in the original array.
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - determines whether the operation will be clockwise or counter-clockwise
 */
void array_8x8_ring_4x4_rotate(uint16_t *arrayPtr, uint8_t direction);

/**
 * @brief refers to the innermost (2x2) box or ring of LEDs in the 8x8 array. 
 *				the pixels are all shifted by a 1-pixel offset in a counter-clockwise circular manner.
 *				performing this operation 4x in succession will result in the original array.
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - determines whether the operation will be clockwise or counter-clockwise
 */
void array_8x8_ring_2x2_rotate(uint16_t *arrayPtr, uint8_t direction);


//-------------------------------RING ROTATE FUNTIONS END----------------------------------------//

/**
 * @brief increases the values of all non-zero values in the array by delta
 * @param[in] arrayPtr - points to the first element within the given array
 * @param[in] delta - the amount in which all non-zero values will be incremented by
 **/
void array_8x8_brighten(uint16_t *arrayPtr, uint16_t delta);

//-------------------------------------------------MODIFY FUNCTIONS END---------------------------------------------------------//

#endif

