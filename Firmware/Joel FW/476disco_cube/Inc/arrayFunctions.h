uint32_t cube[8][8][8];


//Function rotates the cube matrix in any possible direction.
//Esentially a wrapped translate function.
void cubeRotate(uint32_t direction uint32_t *cube[8][8][8])
{
	int x,y;					// x,y are index variables for row, column respectively.
	uint32_t tempUD[8][8];		//temp variable used for layer-wise up/down shifting
	uint32_t tempFB[8];			//temp variable used for row-wise forward/back shifting
	uint32_t tempLR;			//temp variable used for column-wise forward/back shifting
	
	if (direction == "up")
	{
		tempUD = cube[7];
		cube[7] = cube[6];
		cube[6] = cube[5];
		cube[5] = cube[4];
		cube[4] = cube[3];
		cube[3] = cube[2];
		cube[2] = cube[1];
		cube[1] = cube[0];
		cube[0] = tempUD;
	}

	if (direction == "down")
	{
		tempUD = cube[0];
		cube[0] = cube[1];
		cube[1] = cube[2];
		cube[2] = cube[3];
		cube[3] = cube[4];
		cube[4] = cube[5];
		cube[5] = cube[6];
		cube[6] = cube[7];
		cube[7] = tempUD;
	}

	if (direction == "left")
	{
		for (x=0;x<8;x++)
		{
			for (y=0;y<8;y++)
			{
				tempLR = cube[x][y][0]
				cube[x][y][0] = cube[x][y][1];
				cube[x][y][1] = cube[x][y][2];
				cube[x][y][2] = cube[x][y][3];
				cube[x][y][3] = cube[x][y][4];
				cube[x][y][4] = cube[x][y][5];
				cube[x][y][5] = cube[x][y][6];
				cube[x][y][6] = cube[x][y][7];
				cube[x][y][7] = cube[x][y][tempLR];
			}
		}
	}

	if (direction == "right")
	{
		for (x=0;x<8;x++)
		{
			for (y=0;y<8;y++)
			{
				tempLR = cube[x][y][7]
				cube[x][y][7] = cube[x][y][6];
				cube[x][y][6] = cube[x][y][5];
				cube[x][y][5] = cube[x][y][4];
				cube[x][y][4] = cube[x][y][3];
				cube[x][y][3] = cube[x][y][2];
				cube[x][y][2] = cube[x][y][1];
				cube[x][y][1] = cube[x][y][0];
				cube[x][y][0] = cube[x][y][tempLR];
			}
		}	
	}

	//Not sure if this is actually forward or back. Need to verify.
	if (direction == "forward")
	{
		for (x=0;x<8;x++)
		{
			tempFB = cube[x][0];
			cube[x][0]= cube[x][1];
			cube[x][1]= cube[x][2];
			cube[x][2]= cube[x][3];
			cube[x][3]= cube[x][4];
			cube[x][4]= cube[x][5];
			cube[x][5]= cube[x][6];
			cube[x][6]= cube[x][7];
			cube[x][7]= cube[x][tempFB];
		}
	}
	
	//Not sure if this is actually forward or back. Need to verify.
	if (direction == "back")
	{
		for (x=0;x<8;x++)
		{
			tempFB = cube[x][7];
			cube[x][7]= cube[x][6];
			cube[x][6]= cube[x][5];
			cube[x][5]= cube[x][4];
			cube[x][4]= cube[x][3];
			cube[x][3]= cube[x][2];
			cube[x][2]= cube[x][1];
			cube[x][1]= cube[x][0];
			cube[x][0]= cube[x][tempFB];
		}
	}
	
};



