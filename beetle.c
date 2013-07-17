//Jonathan Lehman
//Jan. 21, 2011

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

//declare functions
int randDegree(void);

//main where program runs
int main(int argc, char **argv)
{
	char *invalChar1;
	char *invalChar2;

	//check that there are 3 arguments
	if(argc != 3)
	{
		fprintf(stderr, "There is/are %d argument(s) (not including the file location). There should be 2 integer arguments, board size in inches and number of beetles.\n", argc - 1);
		exit(1);
	}

	long arg1;
	long arg2;
	//perform conversion
	//and check that there is no overflow
	if(((arg1 = strtol(argv[1], &invalChar1, 10)) >= INT_MAX) || ((arg2 = strtol(argv[2], &invalChar2, 10)) >= INT_MAX))
	{
		fprintf(stderr, "Overflow. The arguments: board size, %s, and the number of beetles, %s, must be valid integers less than %d\n", argv[1], argv[2], INT_MAX);
		exit(1);
	}

	//check that arguments are valid integers > 0 also checks underflow error and that there are no characters in the arguments
	if(!(arg1 > 0 && arg2 > 0) || (*invalChar1 || *invalChar2))
	{
		fprintf(stderr, "Both arguments must be valid integers greater than 0. The arguments: board size, %s, and the number of beetles, %s, are not both valid integers greater than 0.\n", argv[1], argv[2]);
		exit(1);
	}

	int boardSize = strtol(argv[1], NULL, 10);
	int numBeetles = strtol(argv[2], NULL, 10);
	int beetleCtr = numBeetles;
	double startPoint = (double) boardSize / 2;
	double locX;
	double locY;
	int degree;
	int dead;

	int elapsedSec;
	int totSec = 0;

	//called to seed random by using time in seconds
	//makes rand() generate truly random numbers
	//kearns does not want to seed
	//srand(time(NULL));

	//iterate until all beetles die
	while(beetleCtr--)
	{
		//for testing
		//printf("Num beetles: %d\n", numBeetles);

		//reset variables
		locX = startPoint;
		locY = startPoint;
		elapsedSec = 0;
		dead = 0;

		while(dead != 1)
		{
			//get random degree
			degree = randDegree();
			int found = 0;

			//for testing
			//printf("Degree: %d\n", degree);

			locX += cos(degree / 180.0 * M_PI);
			locY += sin(degree / 180.0 * M_PI);
			elapsedSec += 1;
			found = 1;

			//for testing
			//printf("Loc X: %f Loc Y: %f\n\n", locX, locY);

			//check if bug died
			if(locX < 0 || locX > boardSize || locY < 0 || locY > boardSize)
			{
				//set bug to dead and add elapsed seconds to total seconds
				dead = 1;
				//for testing
				//printf("Elapsed Sec %d\n", elapsedSec);
				totSec += elapsedSec;
				//for testing
				//printf("Total Sec %d\n", totSec);
			}
			else
			{
				//bug passes out for 1 second
				elapsedSec += 1;
			}
		}

	}

	//print results
	double avgSec = (double) totSec / (double)numBeetles;
	printf("%d by %d square, %d beetle(s), mean beetle lifetime is %.1f\n", boardSize, boardSize, numBeetles, avgSec);

	return 0;
}

//generates a random degree [0,360]
int randDegree(void)
{
	int n;
	n = random() % 361;
	return n;
}
