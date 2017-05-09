/*
 * main.c
 *
 * Created: 5/6/2017 11:57:35 AM
 *  Author: guswe541
 */ 
#include <avr/io.h>
#include "SearchAndFindGurra.h"

int main(void)
{
	xpos = 14;
	ypos = 14;
	direction = 8;
	//(right_distance = 100;
	//left_distance = 100;
	/* Replace with your application code */
	while (1)
	{

		robot_keep_right();
		//robot_move();
	}
}