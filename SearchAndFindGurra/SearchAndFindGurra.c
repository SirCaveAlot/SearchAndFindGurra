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
//#define wall 1 


int xpos;
int ypos;
int direction; 
int right_distance;
int left_distance;
bool finished_with_drive_nearest_path;
//int front_distance =...

	
int map_array[29][29] =
{  //n
//   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
	{0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 0 m
	{0, 0, 0, 0, 0, 0, 5, 0, 1, 1, 1, 1, 5, 0, 0, 5, 1, 1, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 1
	{0, 0, 0, 0, 0, 0, 5, 0, 1, 5, 1, 1, 5, 0, 0, 5, 5, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 2
	{0, 0, 0, 0, 0, 0, 5, 0, 1, 1, 1, 1, 5, 0, 0, 5, 5, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 3
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 5, 5, 0, 0, 0, 5, 5, 5, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 4
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 5, 0, 0, 0, 0, 5, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 5
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 5, 5, 5, 5, 5, 5, 1, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 6
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 7
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 5, 1, 5, 5, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 8
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 9
	{0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 1, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 10
	{0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 1, 1, 1, 1, 5, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 11
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 5, 5, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 12
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0} ,// 13
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 4, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 14
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 15
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 16
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 17
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 18
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 19
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 20
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 21
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 22
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 23
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 24
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 25
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 26
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,// 27
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // 28
};

int robot_array[29][29];

int undiscovered_tiles_array[29][29];

int nearest_path_array[29][29]; //contains the coordinates with the nearest path

int gurras_array[7][3] = //example of what gurras_array might look like
{
	{14, 14, 6,} ,
	{13, 14, 5,} ,
	{12, 14, 4,} ,
	{11, 14, 3,} ,
	{11, 15, 2,} ,
	{11, 16, 1,} ,
	{12, 16, 0,} 
};

void nearest_path_to_array() //takes the coordinates from gurras_array and puts it in nearest_path_array[29][29]
{
	int m = 0; 
	while(gurras_array[m][2] != 0)
	{			
		nearest_path_array[gurras_array[m][0]][gurras_array[m][1]] = 3;
		m++;
	}
	nearest_path_array[gurras_array[m][0]][gurras_array[m][1]] = 3;
	
}


//back at start position?
bool back_at_start(int yposition,int xposition)
{
	if(map_array[yposition][xposition] == 4)
	{	
		robot_turn_around(); //turn around (assuming start position was up)
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

bool detect_outer_wall(int next_yposition,int next_xposition)
{
	if(next_yposition < 0 || next_xposition < 0)
	{
		return false;
	} 
	else if(map_array[next_yposition][next_xposition] == 5)
	{
		return true;
	}
	else if(map_array[next_yposition][next_xposition] == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool detect_path(int next_yposition,int next_xposition, int value) //detects if coordinate is given path coordinate
{
	if(nearest_path_array[next_yposition][next_xposition] == value)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void robot_move() //moves robot one coordinate forward
{
	xpos = next_x_position(direction);
	ypos = next_y_position(direction);
}

void robot_move_distance(int number_of_steps)
{
	for(int i = 0; i < number_of_steps; i++)
	{
		robot_move();
	}
}

void set_coordinate_in_array(int y, int x, int value) //sets coordinate in array to value
{
	robot_array[y][x] = value;
}

void set_coordinate_in_NP_array(int y, int x, int value) //sets coordinate in nearest_path_array to value
{
	nearest_path_array[y][x] = value;
}

//As long as we don't find a wall ahead or a clear at the right hand side, the robot keeps moving forward 
//BUT! if we first off, find a clear way to travel to the right, we turn right and if we find a wall we 
//clearly have to turn left
void robot_keep_right()
{
	while(back_at_start(ypos, xpos) == false)
	{
		save_detected_walls_in_array();
		if(detect_wall(right_y_pos(), right_x_pos())) //as long as we have wall to the right
		{ 
			if(!(detect_wall(next_y_position(direction), next_x_position(direction)))) //and no wall in front of robot
			{ 
				robot_move(); 
				back_at_start(ypos, xpos);
			}
			else
			{
				if(detect_wall(left_y_pos(), left_x_pos()))
				{ 
					robot_turn_around();	//if wall to all sides except back, then turn around	
				}
				else
				{
					robot_turn_left(); //if wall in front of robot and wall to the right then turn left
				}
			}
		}
		else
		{
 			robot_turn_right(); //turn right when possible
			robot_move(); //then move forward
			back_at_start(ypos, xpos);
		}
	}
	robot_detect_outer_walls(); // THIS NEEDS TO BE RUN WITHOUT ACTUALLY CHANGING ROBOTS POSITION
}

bool drive_nearest_path() //follows given path from gurras_array
{
	if(detect_path(next_y_position(direction), next_x_position(direction), 3))
	{
		set_coordinate_in_NP_array(ypos, xpos, 1); // if robot move is outside of while loop in main function, setting coordinate
		robot_move();							   // here will save STARTING and end POSITION as 3 and set rest of path to 1.
		return false;
		
	}
	else if(detect_path(right_y_pos(), right_x_pos(), 3))
	{
		set_coordinate_in_NP_array(ypos, xpos, 1);
		robot_turn_right();
		return false;
	}
	else if(detect_path(left_y_pos(), left_x_pos(), 3))
	{
		set_coordinate_in_NP_array(ypos, xpos, 1);
		robot_turn_left();
		return false;
	}
	else
	{
		finished_with_drive_nearest_path = true;
		return true;
	}

}


bool drive_back_nearest_path() //drives the same way back, drives_nearest_path need to be finished when starting this function
{
	if(detect_path(next_y_position(direction), next_x_position(direction), 1))
	{
		set_coordinate_in_NP_array(ypos, xpos, 2);
		robot_move();
		return false;
		
	}
	else if(detect_path(right_y_pos(), right_x_pos(), 1))
	{
		set_coordinate_in_NP_array(ypos, xpos, 2);
		robot_turn_right();
		return false;
	}
	else if(detect_path(left_y_pos(), left_x_pos(), 1))
	{
		set_coordinate_in_NP_array(ypos, xpos, 2);
		robot_turn_left();
		return false;
	}
	else if(detect_path(back_y_pos(), back_x_pos(), 1))
	{
		set_coordinate_in_NP_array(ypos, xpos, 2);
		robot_turn_right();
		robot_turn_right();
		return false;
	}
	else
	{
		return true;
	}

}

void drive_to_distressed_and_return()
{
	if(finished_with_drive_nearest_path)
	{
			//leave something for distressed
		drive_back_nearest_path();
	}
	else
	{
		drive_nearest_path();
	}
}

void robot_detect_outer_walls()
{
	robot_turn_left();
	robot_move();
	while (map_array[next_y_position(direction)][next_x_position(direction)] != 4)
	{
		save_detected_outer_wall_in_array(ypos, xpos);
		if(detect_outer_wall(right_y_pos(), right_x_pos()))
		{
			robot_turn_right();
			robot_move();
		}
		else if(detect_outer_wall(next_y_position(direction), next_x_position(direction)))
		{
			robot_move();
		}
		else if(detect_outer_wall(left_y_pos(), left_x_pos()))
		{
			robot_turn_left();
		}
		else if(detect_outer_wall(forward_to_left_y_pos(), forward_to_left_x_pos()))
		{
			robot_move();
			robot_turn_left();
			robot_move();
			save_detected_outer_wall_in_array(ypos, xpos);
			robot_turn_around();
			if(detect_outer_wall(forward_to_left_y_pos(), forward_to_left_x_pos()))
			{
				robot_move();
				robot_turn_left();
				robot_move();
				save_detected_outer_wall_in_array(ypos, xpos);
			}
			else
			{
				robot_turn_around();
			}
			
		}
	}
	save_detected_outer_wall_in_array(ypos, xpos);
	find_unknown_cells_after_detection_of_outer_walls();
}

void find_unknown_cells_after_detection_of_outer_walls() //finds unknowns cells inside detected outer walls after robot_keep_right and sets them to 1 inside the undiscovered_tiles_array
{
	int m = 0; //use robot array instead of map array when working 
	while(m < 29)
	{
		int n = 0;
		while(n < 29)
		{
			if(undiscovered_tiles_array[m][n] == 6)
			{
				bool last_6 = false;
				int n2 = n;
				while((undiscovered_tiles_array[m][n2+1] != 6) && !last_6)
				{
					if(n2 > 28)
					{
						last_6 = true;
					}
					else
					{
						n2++;
					}
				}
				while((n <= n2) && !last_6)
				{
					if(map_array[m][n+1] == 0)
					{
						if(m == 0 || m == 28)
						{
							undiscovered_tiles_array[m][n+1] = 0; 
						}
						else 
						{
							undiscovered_tiles_array[m][n+1] = 1; //undetected space
						}
					} 
					else if(map_array[m][n+1] == 1)
					{
						undiscovered_tiles_array[m][n+1] = 2; //free space
					} 
					else if(map_array[m][n+1] == 5 && undiscovered_tiles_array[m][n+1] > 0)
					{
						undiscovered_tiles_array[m][n+1] = 6; //outer wall
					}
					else if(map_array[m][n+1] == 5)
					{
						undiscovered_tiles_array[m][n+1] = 5; //inner wall
					}
					else if(map_array[m][n+1] == 4)
					{
						undiscovered_tiles_array[m][n+1] = 4;
					}
					n++;
				}
			}
			n++;	
		}
		m++;
	}	
}

void find_first_undiscovered_tile()
{
	bool finished = false;
	int m = 0;
	while(m < 29 && !finished)
	{
		int n = 0;
		while(n < 29 && !finished)
		{
			if(undiscovered_tiles_array[m][n] == 1)
			{
				finished = true;
				first_undiscovered_tile_y = m;
				first_undiscovered_tile_x = n;
			}
			n++;	
		}
		m++;
	}	
}
	
void save_detected_walls_in_array() //saves detected walls  as 5 and detected free space as 1 in array
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
	if(map_array[left_y_pos()][left_x_pos()] == 1)
	{
		set_coordinate_in_array(left_y_pos(), left_x_pos(), 1);
	}
}

void save_detected_outer_wall_in_array(int y, int x) //saves detected outer walls  as 6
{
	undiscovered_tiles_array[y][x] = 6;
}

