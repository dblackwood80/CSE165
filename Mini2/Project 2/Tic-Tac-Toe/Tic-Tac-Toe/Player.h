#ifndef PLAYER_H
#define PLAYER_H

#include <time.h>
#include <stdlib.h>
#include "Draw.h"

class Player
{
public:
	std::vector < std::vector< int > > vec1;
	bool player1Turn = true;
	bool keepOnChecking = true;
	//bool aiIsEnabled = false;
	bool enableAI = false;
	bool done = false;
	int randomChoiceX, randomChoiceY;

	Player()
	{
		vec1.assign(3, std::vector<int>(3, 0));
	}

	~Player()
	{
		
	}

	void reset()
	{
		vec1.clear();
		vec1.assign(3, std::vector<int>(3, 0));
		std::cout << "RESET: " << vec1[1][1] << std::endl;
		player1Turn = true;
		keepOnChecking = true;
		done = false;
	}

	void print()
	{
		// << vec1[0][0] << std::endl;
	}

	void playerAI()
	{
		if (enableAI && keepOnChecking && player1Turn == false)
		{
				/* initialize random seed: */
				srand(time(NULL));

				/* generate number between 0 and 2 */
				randomChoiceX = rand() % 3;

				randomChoiceY = rand() % 3;
				std::cout << randomChoiceX << " rand num 1: " << randomChoiceY << std::endl;

				//Finishing moves

				/*if ((vec1[0][0] == 0 && vec1[0][1] == 2 && vec1[0][2] == 2) || (vec1[1][2] == 2 && vec1[2][2] == 2 && vec1[0][0] == 0) || (vec1[2][0] == 2 && vec1[1][1] == 2 && vec1[0][0] == 0)) //left right, top bottom, diagonal
				{
					vec1[0][0] = 2;
					player1Turn = true;
					done = true;
				}*/

				if ((vec1[0][0] == 2 && vec1[0][1] == 2 && vec1[0][2] == 0) || (vec1[1][2] == 2 && vec1[2][2] == 2 && vec1[0][2] == 0) || (vec1[2][0] == 2 && vec1[1][1] == 2 && vec1[0][2] == 0)) //left right, top bottom, diagonal
				{
					vec1[0][2] = 2;
					player1Turn = true;
					done = true;
				}

				else if ((vec1[0][1] == 2 && vec1[1][1] == 2 && vec1[2][1] == 0) || (vec1[2][0] == 2 && vec1[2][2] == 2 && vec1[2][1] == 0)) //top bottom, left right
				{
					vec1[2][1] = 2;
					player1Turn = true;
					done = true;
				}

				else if ((vec1[0][0] == 2 && vec1[1][0] == 0 && vec1[2][0] == 2) || (vec1[1][1] == 2 && vec1[1][2] == 2 && vec1[1][0] == 0)) //top bottom, left right
				{
					vec1[1][0] = 2;
					player1Turn = true;
					done = true;
				}

				//Block move

				if ((vec1[0][0] == 1 && vec1[0][1] == 1 && vec1[0][2] == 0) || (vec1[1][2] == 1 && vec1[2][2] == 1 && vec1[0][2] == 0) || (vec1[2][0] == 1 && vec1[1][1] == 1 && vec1[0][2] == 0)) //left right, top bottom, diagonal
				{
					vec1[0][2] = 2;
					player1Turn = true;
					done = true;
				}

				else if ((vec1[0][1] == 1 && vec1[1][1] == 1 && vec1[2][1] == 0) || (vec1[2][0] == 1 && vec1[2][2] == 1 && vec1[2][1] == 0)) //top bottom, left right
				{
					vec1[2][1] = 2;
					player1Turn = true;
					done = true;
				}

				else if ((vec1[0][0] == 1 && vec1[1][0] == 0 && vec1[2][0] == 1) || (vec1[1][1] == 1 && vec1[1][2] == 1 && vec1[1][0] == 0)) //top bottom, left right
				{
					vec1[1][0] = 2;
					player1Turn = true;
					done = true;
				}

				if (vec1[randomChoiceX][randomChoiceY] == 0 && done == false)
				{
					std::cout << "\nshould 1 work X: " << randomChoiceX << " Y: " << randomChoiceY << std::endl;
					vec1[randomChoiceX][randomChoiceY] = 2;
					player1Turn = true;
					done = true;
				}

				if (done == false)
				{
					for (int i = 0; i < 20; i++)
					{
						/* generate number between 0 and 2 */
						randomChoiceX = rand() % 3;

						randomChoiceY = rand() % 3;
						std::cout << randomChoiceX << " rand num 2: " << randomChoiceY << std::endl;

						if (vec1[randomChoiceX][randomChoiceY] == 0)
						{
							vec1[randomChoiceX][randomChoiceY] = 2;
							std::cout << "\nshould 2 work X: " << randomChoiceX << " Y: " << randomChoiceY << std::endl;
							player1Turn = true;
							done = true;
							break;
						}
					}
				}				
		}
	}

	void inBounds(float x, float y)
	{
		if (keepOnChecking)
		{
			//First row logic
			//--------------------------------------------------------------------------------------------------------------\\

			if (x >= 0 && x <= 210 && y >= 0 && y <= 205)
			{
				if (player1Turn)
				{
					if (vec1[0][0] == 0)
					{
						vec1[0][0] = 1;
						player1Turn = false;
					}
				}
				else if (vec1[0][0] == 0)
				{
					vec1[0][0] = 2;
					player1Turn = true;
				}
			}

			if (x >= 215 && x <= 425 && y >= 0 && y <= 205)
			{
				if (player1Turn)
				{
					if (vec1[0][1] == 0)
					{
						vec1[0][1] = 1;
						player1Turn = false;
					}
				}
				else if (vec1[0][1] == 0)
				{
					vec1[0][1] = 2;
					player1Turn = true;
				}
			}

			if (x >= 430 && x <= 660 && y >= 0 && y <= 205)
			{
				if (player1Turn)
				{
					if (vec1[0][2] == 0)
					{
						vec1[0][2] = 1;
						player1Turn = false;
					}
				}
				else if (vec1[0][2] == 0)
				{
					vec1[0][2] = 2;
					player1Turn = true;
				}
			}

			//Second row logic
			//--------------------------------------------------------------------------------------------------------------\\

			if (x >= 0 && x <= 210 && y >= 213 && y <= 432)
			{
				if (player1Turn)
				{
					if (vec1[1][0] == 0)
					{
						vec1[1][0] = 1;
						player1Turn = false;
					}
				}
				else if (vec1[1][0] == 0)
				{
					vec1[1][0] = 2;
					player1Turn = true;
				}
			}

			if (x >= 215 && x <= 425 && y >= 213 && y <= 432)
			{
				if (player1Turn)
				{
					if (vec1[1][1] == 0)
					{
						vec1[1][1] = 1;
						player1Turn = false;
					}

				}
				else if (vec1[1][1] == 0)
				{
					vec1[1][1] = 2;
					player1Turn = true;
				}
			}

			if (x >= 430 && x <= 660 && y >= 213 && y <= 432)
			{
				if (player1Turn)
				{
					if (vec1[1][2] == 0)
					{
						vec1[1][2] = 1;
						player1Turn = false;
					}
				}
				else if (vec1[1][2] == 0)
				{
					vec1[1][2] = 2;
					player1Turn = true;
				}
			}

			//Third row logic
			//--------------------------------------------------------------------------------------------------------------\\


			if (x >= 0 && x <= 210 && y >= 439 && y <= 660)
			{
				if (player1Turn)
				{
					if (vec1[2][0] == 0)
					{
						vec1[2][0] = 1;
						player1Turn = false;
					}
				}
				else if (vec1[2][0] == 0)
				{
					vec1[2][0] = 2;
					player1Turn = true;
				}

			}

			if (x >= 215 && x <= 425 && y >= 439 && y <= 660)
			{
				if (player1Turn)
				{
					if (vec1[2][1] == 0)
					{
						vec1[2][1] = 1;
						player1Turn = false;
					}

				}
				else if (vec1[2][1] == 0)
				{
					vec1[2][1] = 2;
					player1Turn = true;
				}
			}

			if (x >= 430 && x <= 660 && y >= 439 && y <= 660)
			{
				if (player1Turn)
				{
					if (vec1[2][2] == 0)
					{
						vec1[2][2] = 1;
						player1Turn = false;
					}

				}
				else if (vec1[2][2] == 0)
				{
					vec1[2][2] = 2;
					player1Turn = true;
				}
			}
		}

		
	}

	int player1Won()
	{
		if (keepOnChecking)
		{
			//First row logic
	//--------------------------------------------------------------------------------------------------------------\\

			if (vec1[0][0] == 1 && vec1[0][1] == 1 && vec1[0][2] == 1)
			{
				return 0;
			}
			else if (vec1[1][0] == 1 && vec1[1][1] == 1 && vec1[1][2] == 1)
			{
				return 0;
			}
			else if (vec1[2][0] == 1 && vec1[2][1] == 1 && vec1[2][2] == 1)
			{
				return 0;
			}
			else if (vec1[0][0] == 1 && vec1[1][0] == 1 && vec1[2][0] == 1)
			{
				return 0;
			}
			else if (vec1[0][1] == 1 && vec1[1][1] == 1 && vec1[2][1] == 1)
			{
				return 0;
			}
			else if (vec1[0][2] == 1 && vec1[1][2] == 1 && vec1[2][2] == 1)
			{
				return 0;
			}
			else if (vec1[0][0] == 1 && vec1[1][1] == 1 && vec1[2][2] == 1)
			{
				return 0;
			}
			else if (vec1[0][2] == 1 && vec1[1][1] == 1 && vec1[2][0] == 1)
			{
				return 0;
			}
			else if (vec1[0][0] == 2 && vec1[0][1] == 2 && vec1[0][2] == 2)
			{
				return 1;
			}
			else if (vec1[1][0] == 2 && vec1[1][1] == 2 && vec1[1][2] == 2)
			{
				return 1;
			}			
			else if (vec1[2][0] == 2 && vec1[2][1] == 2 && vec1[2][2] == 2)
			{
				return 1;
			}
			else if (vec1[0][0] == 2 && vec1[1][0] == 2 && vec1[2][0] == 2)
			{
				return 1;
			}			
			else if (vec1[0][1] == 2 && vec1[1][1] == 2 && vec1[2][1] == 2)
			{
				return 1;
			}			
			else if (vec1[0][2] == 2 && vec1[1][2] == 2 && vec1[2][2] == 2)
			{
				return 1;
			}		
			else if (vec1[0][0] == 2 && vec1[1][1] == 2 && vec1[2][2] == 2)
			{
				return 1;
			}
			else if (vec1[0][2] == 2 && vec1[1][1] == 2 && vec1[2][0] == 2)
			{
				return 1;
			}
			else 
			{
				if (vec1[0][0] != 0 && vec1[0][1] != 0 && vec1[0][2] != 0 && vec1[1][0] != 0 && vec1[1][1] != 0 && vec1[1][2] != 0 && vec1[2][0] != 0 && vec1[2][1] != 0 && vec1[2][2] != 0)
				{
					//std::cout << "TIE" << std::endl;
					return 2;
				}
			}
		}
	}
};

#endif // !PLAYER_H
