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
	set_coordinate_in_array(ypos, xpos, 4);	
	set_coordinate_in_array(left_y_pos() , left_x_pos(), 5);	
	set_coordinate_in_array(right_y_pos() , right_x_pos(), 5);	
	robot_move();
	nearest_path_to_array();
	//(right_distance = 100;
	//left_distance = 100;
	/* Replace with your application code */
	while (1)
	{

		//robot_keep_right();
		drive_nearest_path();
		//robot_move();
	}
}