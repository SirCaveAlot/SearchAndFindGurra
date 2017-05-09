/*
 * SearchAndFindGurra.c
 *
 * Created: 5/6/2017 8:41:13 AM
 *  Author: guswe541
 */ 


#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include "SearchAndFindGurra.h"

#define up 8
#define down 2
#define left 4 
#define right 6
#define wall 1 


int xpos;
int ypos;
int direction; 
int right_distance;
int left_distance;
//int front_distance =...

	
int map_array[29][29] =
{
//   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
	{0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 0
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 5, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 1
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 5, 1, 1, 1, 5, 1, 5, 5, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 2
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 3
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 4
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 5
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 6
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 7
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 5, 5, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 8
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 9
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 10
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 11
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 1, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 12
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 13
	{0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 4, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 14
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 15
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 16
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 17
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 18
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 19
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 20
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 21
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 22
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 23
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 24
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 25
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 26
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,} ,// 27
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}  // 28
};


int robot_array[29][29];

//changing robot direction to given direction
void robot_set_direction(int next_direction)
{
	direction = next_direction;
}

//always turning right in relation to where it's heading
void robot_turn_right()
{
	if(direction == up)
	{		 
		robot_set_direction(right);
	}
	else if(direction == right)
	{		
		robot_set_direction(down);
	}	
	else if(direction == down)
	{		
		robot_set_direction(left);
	}
	else if(direction == left)
	{		
		robot_set_direction(up);
	}	
}

//always turning left in relation to where it's heading
void robot_turn_left()
{
	if(direction ==  up)
	{
		robot_set_direction(left);
	}
	else if(direction == right)
	{
		robot_set_direction(up);
	}
	else if(direction == down)
	{
		robot_set_direction(right);
	}
	else if(direction == left)
	{
		robot_set_direction(down);
	} 
}

//calculates next pos (general) 
int next_y_position(int next_direction)
{
	int next_ypos;
	next_ypos = ypos;
	
	if(next_direction == up)
	{
		next_ypos--;
	}
	else if(next_direction == down)
	{
		next_ypos++;
	}
	return next_ypos;
}
int next_x_position(int next_direction)
{
	int next_xpos;
	next_xpos = xpos;
	
	if(next_direction == right)
	{
		next_xpos++;
	}
	else if(next_direction == left)
	{
		next_xpos--;
	}
	return next_xpos;
}

//calculates robots next pos
int robot_xpos_right()
{
	int right_xpos = 0;
	if(direction == up)
	{
		right_xpos = next_x_position(right);
	}
	else if(direction == down)
	{
		right_xpos = next_x_position(left);
	}
	else if(direction == right)
	{
 		right_xpos = next_x_position(down);
	}
	else if(direction == left)
	{
		right_xpos = next_x_position(up);
	}
	return right_xpos;
}
// 
// 
int robot_ypos_right()
{
	int right_ypos = 0;
	if(direction == up)
	{
		right_ypos = next_y_position(right);
	}
	else if(direction == down)
	{
		right_ypos = next_y_position(left);
	}
	else if(direction == right)
	{
		right_ypos = next_y_position(down);
	}
	else if(direction == left)
	{
		right_ypos = next_y_position(up);
	}
	return right_ypos;
}

//back at start position?
bool back_at_start(int yposition,int xposition)
{
	if(map_array[yposition][xposition] == 4)
	{	
		robot_turn_right();
		robot_turn_right(); //turn around (assuming start position was up)
		return true; // right-lap is finished
	}
	else
	{	
		return false;
	}
}
//detecting walls 
bool detect_wall(int next_yposition,int next_xposition)
{
	if(map_array[next_yposition][next_xposition] == 0)
	{
		return true;	
	}
	else if(map_array[next_yposition][next_xposition] == 1)
	{
		return false;
	}
	else if(map_array[next_yposition][next_xposition] == 2)
	{
		return true;
	}
	else if(map_array[next_yposition][next_xposition] == 4)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

void robot_move()
{
	xpos = next_x_position(direction);
	ypos = next_y_position(direction);
// 	xpos = robot_next_xpos_forward();
// 	ypos = robot_next_ypos_forward();
}

void robot_move_distance(int number_of_steps)
{
	for(int i = 0; i < number_of_steps; i++)
	{
		robot_move();
	}
}

//As long as we don't find a wall ahead or a clear at the right hand side, the robot keeps moving forward 
//BUT! if we first off, find a clear way to travel to the right, we turn right and if we find a wall we 
//clearly have to turn left
void robot_keep_right()
{
	save_detected_walls_in_array();
	//robot_next_yposition= next_ypos(robot.direction);
	//robot_next_xposition= next_xpos(robot.direction)
	if(detect_wall(robot_ypos_right(), robot_xpos_right()))
	{ //as long as we have wall to the right
		if(!(detect_wall(next_y_position(direction), next_x_position(direction))))
		{ //and no wall in front of robot
			robot_move(); 
			back_at_start(ypos, xpos);
		}
		else
		{
			robot_turn_left(); //if wall in front of robot and wall to the right then turn left
		}
	}
	else
	{
 		robot_turn_right(); //turn right when possible
		robot_move(); //then move forward
		back_at_start(ypos, xpos);
	}
}

void set_coordinate_in_array(int y, int x, int value)
{
	robot_array[y][x] = value;
}

{
	
	/*
void set_coordinate_in_array(int y, int x, int value)
{
	robot_array[y][x] = value;
}

*/
	
void save_detected_walls_in_array()
{	
	set_coordinate_in_array(ypos, xpos, 1);
	//if(right_distance < 150)
	if(map_array[right_y_pos()][right_x_pos()] >= 5)
	{
		set_coordinate_in_array(right_y_pos(), right_x_pos(), 5);	
	}
	//if(left_distance < 150)
	if(map_array[left_y_pos()][left_x_pos()] >= 5)
	{
		set_coordinate_in_array(left_y_pos(), left_x_pos(), 5);
	}
	if(map_array[right_y_pos()][right_x_pos()] == 1)
	{
		set_coordinate_in_array(right_y_pos(), right_x_pos(), 1);
	}
	if(map_array[right_y_pos()][right_x_pos()] == 1)
	{
		set_coordinate_in_array(left_y_pos(), left_x_pos(), 1);
	}
}

//position to the right of the robot x coordinates
int right_x_pos()
{
	int right_x_pos;
	right_x_pos = xpos;
	if(direction == up)
	{
		right_x_pos = xpos +1;
	}
	else if(direction == down)
	{
		right_x_pos = xpos -1;
	}
	else if(direction == left)
	{
		right_x_pos = xpos;
	}
	else if(direction == right)
	{
		right_x_pos = xpos;
	}
	return right_x_pos;
}
	
//position to the right of the robot y coordinates
int right_y_pos()
{
	int right_y_pos = ypos;
	if(direction == up)
	{
		right_y_pos = ypos;
	}
	else if(direction == down)
	{
		right_y_pos = ypos;
	}
	else if(direction == left)
	{
		right_y_pos = ypos -1;
	}
	else if(direction == right)
	{
		right_y_pos = ypos +1;
	}
	return right_y_pos;
}

//position to the left of the robot x coordinates
int left_x_pos()
{
	int left_x_pos = xpos;
	if(direction == up)
	{
		left_x_pos = xpos -1;
	}
	else if(direction == down)
	{
		left_x_pos = xpos +1;
	}
	else if(direction == left)
	{
		left_x_pos = xpos;
	}
	else if(direction == right)
	{
		left_x_pos = xpos;
	}
	return left_x_pos;
}

//position to the left of the robot y coordinates
int left_y_pos()
{
	int left_y_pos = xpos;
	if(direction == up)
	{
		left_y_pos = ypos;
	}
	else if(direction == down)
	{
		left_y_pos = ypos;
	}
	else if(direction == left)
	{
		left_y_pos = ypos +1;
	}
	else if(direction == right)
	{
		left_y_pos = ypos -1;
	}
	return left_y_pos;
}
