/*
 * main.cpp
 *
 * print employees' id and score.
 * Duplicated random number avoidance
 *
 * Author : Jungmo Ahn <ajm100@ajou.ac.kr>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

struct info {
	char id[8];
	unsigned int score;
}; //structure for saving employee's information

uint32_t checkRan[3125];
//0 to 100000 number of bits 

int checkDuplicated(unsigned int ran);

int main(int argc, char** argv)
{
	unsigned int ran;
	unsigned int loop = atoi(argv[1]);
	unsigned int i;
	struct info* list;
	
	if(!(0 < loop && loop < 100000))
	{
		fprintf(stderr, "Invalid Input\n");
		return 0;
	}
	srand((unsigned int) time(NULL));
	list = (struct info *)malloc(sizeof(struct info)*loop);
	
	for(i = 0; i < loop; i++)
	{
		//for id
		ran = rand()%100000;
	
		if(checkDuplicated(ran) == -1)
		{
			i--;
			continue;
		}
		sprintf(list[i].id,"NT%05d", ran);
		
		//for score
		ran = rand()%100;
		list[i].score = ran;
	}

	for(i = 0; i < loop; i++)
	{
		printf("%s %4d\n", list[i].id, list[i].score);
	}

	free(list);

	return 0;
}

int checkDuplicated(unsigned int ran)
{
	int idx = 0;
	int bit = 0;
	uint32_t temp = 0;
	idx = ran >> 5;
	bit = ran % 32;
	
	if( (checkRan[idx] & (1<<bit)) != 0 )
	{
		return -1;
	}
	else
	{
		temp = checkRan[idx];
		checkRan[idx] = checkRan[idx] | (1 << (bit));
	}

	return 0;
}
