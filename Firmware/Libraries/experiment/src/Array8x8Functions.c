/*
 * Array8x8Functions.c
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
 **/
void array_8x8_shift_right(uint16_t *arrayPtr)
{
	for (int index=63;index>0;index--)
	{
		*(arrayPtr + index) = *(arrayPtr + index - 1);
	}
	array_8x8_set_column(arrayPtr,0,0x0000);
}


/**
 * @brief shifts the 8x8 array left
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 */
void array_8x8_shift_left(uint16_t arrayPtr)
{
	for (int index=0;index<63;index++)
	{
		*(arrayPtr + index) = *(arrayPtr + index + 1);
	}
	array_8x8_set_column(arrayPtr,7,0x0000);
}


 /**
 * @brief shifts the 8x8 array forward
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 */
void array_8x8_shift_forward(uint16_t arrayPtr)
{
	for (int index=63;index>7;index--)
	{
		*(arrayPtr + index) = *(arrayPtr + index - 8);
	}
	array_8x8_set_row(arrayPtr,0,0x0000);
}


/**
 * @brief shifts the 8x8 array back
 * @param[in] arrayPtr - points to the first element of the given 8x8 array
 */
void array_8x8_shift_back(uint16_t arrayPtr)
{
	for (int index=0;index<56;index++)
	{
		*(arrayPtr + index) = *(arrayPtr + index + 8);
	}
	array_8x8_set_row(arrayPtr,7,0x0000);
}