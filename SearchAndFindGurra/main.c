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
	finished_with_drive_nearest_path = false;	
	set_coordinate_in_array(left_y_pos() , left_x_pos(), 5);	
	set_coordinate_in_array(right_y_pos() , right_x_pos(), 5);
	set_coordinate_in_array(ypos, xpos, 4);
	nearest_path_to_array();
	set_coordinate_in_NP_array(ypos, xpos, 1);
	robot_move();	//pay attention to this
	//right_distance = 100;
	//left_distance = 100;
	/* Replace with your application code */
	robot_keep_right();
	while (1)
	{
		
		
		//drive_to_distressed_and_return();
	}
}