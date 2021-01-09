/*
 * array_8x8.c
 *
 *  Created on: Nov 22, 2020
 *      Author: Joel Michaelis
 */

#include "array_8x8.h"

/**
 * @brief sets a single value within the array
 * @param[in] arrayPtr - points to the first element within the given array
 * @param[in] arrayIndex - specifies which element within the given array to be set
 * @param[in] value - the value which the given array element will be set to
 **/
void array_8x8_set_single(uint16_t *arrayPtr, int arrayIndex, uint16_t value)
{
	*(arrayPtr + arrayIndex) = value;
}


/**
 * @brief sets array values iteratively with a for loop
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] startIndex - initial element in the aray to be set
 * @param[in] stepIndex - step size of the for loop
 * @param[in] stopIndex - final element in the aray to be set
 * @param[in] value - the value that all elements in the given loop will be set to
 **/
void array_8x8_set_multiple(uint16_t *arrayPtr, int startIndex, int stepIndex, int stopIndex, uint16_t value)
{
	for (int tempIndex=startIndex;tempIndex<stopIndex+1;tempIndex=tempIndex+stepIndex)
	{
		*(arrayPtr + tempIndex) = value;
	}
}


/**
 * @brief 
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] column - the column number of 0 through 7
 * @param[in] value - the value that all elements in the given column will be set to
 **/
void array_8x8_set_column(uint16_t *arrayPtr, int column, uint16_t value)
{
	if (column == 0) array_8x8_set_multiple(arrayPtr,0,8,56,value);		//*(arrayPtr[0,8,16,24,32,40,48,56])  = value;
	if (column == 1) array_8x8_set_multiple(arrayPtr,1,8,57,value);		//*(arrayPtr[1,9,17,25,33,41,49,57])  = value;
	if (column == 2) array_8x8_set_multiple(arrayPtr,2,8,58,value);		//*(arrayPtr[2,10,18,26,34,42,50,58]) = value;
	if (column == 3) array_8x8_set_multiple(arrayPtr,3,8,59,value);		//*(arrayPtr[3,11,19,27,35,43,51,59]) = value;
	if (column == 4) array_8x8_set_multiple(arrayPtr,4,8,60,value);		//*(arrayPtr[4,12,20,28,36,44,52,60]) = value;
	if (column == 5) array_8x8_set_multiple(arrayPtr,5,8,61,value);		//*(arrayPtr[5,13,21,29,37,45,53,61]) = value;
	if (column == 6) array_8x8_set_multiple(arrayPtr,6,8,62,value);		//*(arrayPtr[6,14,22,30,38,46,54,62]) = value;
	if (column == 7) array_8x8_set_multiple(arrayPtr,7,8,63,value);		//*(arrayPtr[7,15,23,31,39,47,55,63]) = value;
	return;
}


/**
 * @brief 
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] row - the row number of 0 through 7
 * @param[in] value - the value that all elements in the given row will be set to
 **/
void array_8x8_set_row(uint16_t *arrayPtr, int row, uint16_t value)
{
	if (row == 0) array_8x8_set_multiple(arrayPtr,0,1,7,value);
	if (row == 1) array_8x8_set_multiple(arrayPtr,8,1,15,value);
	if (row == 2) array_8x8_set_multiple(arrayPtr,16,1,23,value);
	if (row == 3) array_8x8_set_multiple(arrayPtr,24,1,31,value);
	if (row == 4) array_8x8_set_multiple(arrayPtr,32,1,39,value);
	if (row == 5) array_8x8_set_multiple(arrayPtr,40,1,47,value);
	if (row == 6) array_8x8_set_multiple(arrayPtr,48,1,55,value);
	if (row == 7) array_8x8_set_multiple(arrayPtr,56,1,63,value);
	return;
}

/**
 * @brief  shifts the 8x8 array in the specified direction.
 *				 zeros are shifted in where applicable
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 **/
 void array_8x8_shift(uint16_t *arrayPtr, uint8_t direction)
 {
	 if (direction == DIRECTION_RIGHT)
	 {
			for (int index=63;index>0;index--)
			{
				*(arrayPtr + index) = *(arrayPtr + index - 1);
			}
			array_8x8_set_column(arrayPtr,0,0x0000);
	 }
	 
	 if (direction == DIRECTION_LEFT)
	 {
			for (int index=0;index<63;index++)
			{
				*(arrayPtr + index) = *(arrayPtr + index + 1);
			}
			array_8x8_set_column(arrayPtr,7,0x0000);
	 }
	 
	 if (direction == DIRECTION_FORWARD)
	 {
			for (int index=63;index>7;index--)
			{
				*(arrayPtr + index) = *(arrayPtr + index - 8);
			}
			array_8x8_set_row(arrayPtr,0,0x0000);
	 }
	 
	 if (direction == DIRECTION_BACK)
	 {
			for (int index=0;index<56;index++)
			{
				*(arrayPtr + index) = *(arrayPtr + index + 8);
			}
			array_8x8_set_row(arrayPtr,7,0x0000);
	 }
 }

/**
 * @brief  shifts the 8x8 array in the specified direction and wraps around. zeros aren't shifted in.
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 **/
void array_8x8_rotate(uint16_t *arrayPtr, uint8_t direction)
{
	
	if (direction == DIRECTION_RIGHT)
	{
		uint16_t tempColumn[8];
		int columnIndex;
		
		//encode tempColumn
		columnIndex=0;
		for (int arrIndex=0;arrIndex<57;arrIndex=arrIndex+8)
		{
			tempColumn[columnIndex] = *(arrayPtr + arrIndex + 7);
			columnIndex++;
		}
		
		array_8x8_shift(arrayPtr, DIRECTION_RIGHT);
		
		//decode tempColumn
		columnIndex=0;
		for(int arrIndex=0;arrIndex<57;arrIndex=arrIndex+8)
		{
			*(arrayPtr + arrIndex) = tempColumn[columnIndex];
			columnIndex++;
		}
	}

	if (direction == DIRECTION_LEFT)
	{
		uint16_t tempColumn[8];
		int columnIndex;
		
		//tempColumn = column0
		columnIndex=0;
		for (int arrIndex=0;arrIndex<57;arrIndex=arrIndex+8)
		{
			tempColumn[columnIndex] = *(arrayPtr + arrIndex);
			columnIndex++;
		}
		
		array_8x8_shift(arrayPtr, DIRECTION_LEFT);
		
		// column7 = tempColumn
		columnIndex=0;
		for(int arrIndex=0;arrIndex<57;arrIndex=arrIndex+8)
		{
			*(arrayPtr + arrIndex + 7) = tempColumn[columnIndex];
			columnIndex++;
		}
	}

	if (direction == DIRECTION_FORWARD)
	{
		uint16_t tempRow[8];
		int rowIndex;
		
		//tempRow = row7
		rowIndex=0;
		for (int arrIndex=56;arrIndex<64;arrIndex++)
		{
			tempRow[rowIndex] = *(arrayPtr + arrIndex);
			rowIndex++;
		}
		
		array_8x8_shift(arrayPtr, DIRECTION_FORWARD);
		
		// row0 = tempRow
		rowIndex=0;
		for(int arrIndex=0;arrIndex<8;arrIndex++)
		{
			*(arrayPtr + arrIndex) = tempRow[rowIndex];
			rowIndex++;
		}
	}

	if (direction == DIRECTION_BACK)
	{
		uint16_t tempRow[8];
		int rowIndex;
		
		//tempRow = row0
		rowIndex=0;
		for (int arrIndex=0;arrIndex<8;arrIndex++)
		{
			tempRow[rowIndex] = *(arrayPtr + arrIndex);
			rowIndex++;
		}
		
		array_8x8_shift(arrayPtr, DIRECTION_BACK);
		
		// row7 = tempRow
		rowIndex=0;
		for(int arrIndex=56;arrIndex<64;arrIndex++)
		{
			*(arrayPtr + arrIndex) = tempRow[rowIndex];
			rowIndex++;
		}
	}
}	 
 
/**
 * @brief  inverts all elements of the array by subtracting the original value from the max possible value
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 **/
void array_8x8_invert(uint16_t *arrayPtr)
{
	for(uint8_t arrayIndex=0;arrayIndex<64;arrayIndex++)
	{
		*(arrayPtr + arrayIndex) = (MAX_BRIGHTNESS - (*(arrayPtr + arrayIndex)));
	}
}	 



/**
 * @brief shifts a column of the 8x8 array in a specified direction. a zero is shifted in
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] colNum - indicates which column is to be shifted (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 */
void array_8x8_shift_column(uint16_t *arrayPtr, uint8_t colNum, uint8_t direction)
{
	if (direction == DIRECTION_FORWARD)
	 {
			for (int index=56+colNum;index>7;index=index-8)
			{
				*(arrayPtr + index) = *(arrayPtr + index - 8);
			}
			array_8x8_set_single(arrayPtr,colNum,0x0000);
	 }
	 
	if (direction == DIRECTION_BACK)
	 {
			for (int index=colNum;index<56;index=index+8)
			{
				*(arrayPtr + index) = *(arrayPtr + index + 8);
			}
			array_8x8_set_single(arrayPtr,56+colNum,0x0000);
	 }
	 
	 if (direction == DIRECTION_INWARD)
	 {
		 *(arrayPtr + colNum + 32) = *(arrayPtr + colNum + 40);
		 *(arrayPtr + colNum + 40) = *(arrayPtr + colNum + 48);
		 *(arrayPtr + colNum + 48) = *(arrayPtr + colNum + 56);
		 *(arrayPtr + colNum + 56) = 0x0000;
		 // --------------- symmetry line---------------------//
		 *(arrayPtr + colNum + 24) = *(arrayPtr + colNum + 16);
		 *(arrayPtr + colNum + 16) = *(arrayPtr + colNum + 8);
		 *(arrayPtr + colNum + 8) = *(arrayPtr + colNum + 0);
		 *(arrayPtr + colNum + 0) = 0x000;
	 }
	 
	 if (direction == DIRECTION_OUTWARD)
	 {
		 *(arrayPtr + colNum + 56) = *(arrayPtr + colNum + 48);
		 *(arrayPtr + colNum + 48) = *(arrayPtr + colNum + 40);
		 *(arrayPtr + colNum + 40) = *(arrayPtr + colNum + 32);
		 *(arrayPtr + colNum + 32) = 0x0000;
		 // --------------- symmetry line---------------------//
		 *(arrayPtr + colNum + 0) = *(arrayPtr + colNum + 8);
		 *(arrayPtr + colNum + 8) = *(arrayPtr + colNum + 16);
		 *(arrayPtr + colNum + 16) = *(arrayPtr + colNum + 24);
		 *(arrayPtr + colNum + 24) = 0x0000;		 
	 }
}

/**
 * @brief shifts a column of the 8x8 array in a specified direction and wraps around
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] colNum - indicates which column is to be rotated (0 - 7)
 * @param[in] direction - specify a preprocessor #defined name that corresponds to a direction
 */
void array_8x8_rotate_column(uint16_t *arrayPtr, uint8_t colNum, uint8_t direction)
{
	uint16_t tempElement = 0;
	
	if (direction == DIRECTION_FORWARD)
	{
		tempElement = *(arrayPtr + 56 + colNum);
		array_8x8_shift_column(arrayPtr, colNum, direction);
		*(arrayPtr + colNum) = tempElement;
	}	
	
	if (direction == DIRECTION_BACK)
	{
		tempElement = *(arrayPtr + colNum);
		array_8x8_shift_column(arrayPtr, colNum, direction);
		*(arrayPtr + 56 + colNum) = tempElement;
	}
}

/**
 * @brief shifts the 8x8 array forward
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] rowNum - indicates which row is to be shifted (0 - 7)
 * @param[in] direction - the desired shift direction
 */
void array_8x8_shift_row(uint16_t *arrayPtr, uint8_t rowNum, uint8_t direction)
{
	if (direction == DIRECTION_RIGHT)
	 {
			for (int index=((8*rowNum)+7);index>(8*rowNum);index--)
			{
				*(arrayPtr + index) = *(arrayPtr + index - 1);
			}
			array_8x8_set_single(arrayPtr,8*rowNum,0x0000);
	 }
	
	if (direction == DIRECTION_LEFT)
	 {
			for (int index=(8*rowNum);index<8*rowNum+7;index++)
			{
				*(arrayPtr + index) = *(arrayPtr + index + 1);
			}
			array_8x8_set_single(arrayPtr,8*rowNum+7,0x0000);
	 }
	 
		 if (direction == DIRECTION_INWARD)
	 {
		 *(arrayPtr + (8*rowNum) + 3) = *(arrayPtr + (8*rowNum) + 2);
		 *(arrayPtr + (8*rowNum) + 2) = *(arrayPtr + (8*rowNum) + 1);
		 *(arrayPtr + (8*rowNum) + 1) = *(arrayPtr + (8*rowNum) + 0);
		 *(arrayPtr + (8*rowNum) + 0) = 0x0000;
		 // --------------- symmetry line---------------------//
		 *(arrayPtr + (8*rowNum) + 4) = *(arrayPtr + (8*rowNum) + 5);
		 *(arrayPtr + (8*rowNum) + 5) = *(arrayPtr + (8*rowNum) + 6);
		 *(arrayPtr + (8*rowNum) + 6) = *(arrayPtr + (8*rowNum) + 7);
		 *(arrayPtr + (8*rowNum) + 7) = 0x0000;
	 }
	 
	 if (direction == DIRECTION_OUTWARD)
	 {
		 *(arrayPtr + (8*rowNum) + 0) = *(arrayPtr + (8*rowNum) + 1);
		 *(arrayPtr + (8*rowNum) + 1) = *(arrayPtr + (8*rowNum) + 2);
		 *(arrayPtr + (8*rowNum) + 2) = *(arrayPtr + (8*rowNum) + 3);
		 *(arrayPtr + (8*rowNum) + 3) = 0x0000;
		 // --------------- symmetry line---------------------//
		 *(arrayPtr + (8*rowNum) + 7) = *(arrayPtr + (8*rowNum) + 6);
		 *(arrayPtr + (8*rowNum) + 6) = *(arrayPtr + (8*rowNum) + 5);
		 *(arrayPtr + (8*rowNum) + 5) = *(arrayPtr + (8*rowNum) + 4);
		 *(arrayPtr + (8*rowNum) + 4) = 0x0000;		 
	 }
}

/**
 * @brief shifts a row of the 8x8 array in a specified direction and wraps around
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 * @param[in] rowNum - indicates which row is to be rotated (0 - 7)
 * @param[in] direction - the desired shift direction
 */
void array_8x8_rotate_row(uint16_t *arrayPtr, uint8_t rowNum, uint8_t direction)
{
	uint16_t tempElement = 0;
	
	if (direction == DIRECTION_RIGHT)
	{
		tempElement = *(arrayPtr + (rowNum*8) + 7);
		array_8x8_shift_row(arrayPtr, rowNum, direction);
		*(arrayPtr + (rowNum*8)) = tempElement;
	}	
	
	if (direction == DIRECTION_LEFT)
	{
		tempElement = *(arrayPtr + (rowNum*8));
		array_8x8_shift_row(arrayPtr, rowNum, direction);
		*(arrayPtr + (rowNum*8) + 7) = tempElement;
	}
}




/**
 * @brief increases the values of all non-zero values in the array by delta
 * @param[in] arrayPtr - points to the first element within the given array
 * @param[in] delta - the amount in which all non-zero values will be incremented by
 **/
void array_8x8_brighten(uint16_t *arrayPtr, uint16_t delta)
{
	for(int arrIndex=0;arrIndex<64;arrIndex++)
	{
		if (*(arrayPtr + arrIndex) != 0x0000) *(arrayPtr + arrIndex) = (*(arrayPtr + arrIndex) + delta);
	}
}
