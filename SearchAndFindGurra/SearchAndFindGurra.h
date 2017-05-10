/*
 * SearchAndFindGurra.h
 *
 * Created: 5/6/2017 11:57:51 AM
 *  Author: guswe541
 */ 

#include <stdbool.h>

#ifndef SEARCHANDFINDGURRA_H_
#define SEARCHANDFINDGURRA_H_

extern int xpos;
extern int ypos;
extern int direction;
//extern int right_distance;
//extern int left_distance;

void robot_set_direction(int next_direction);

void robot_turn_right();

void robot_turn_left();

int next_x_position(int);

int next_y_position(int);

int robot_xpos_right();

int robot_ypos_right();

bool detect_wall(int next_xposition, int next_yposition);

void robot_move();

void robot_move_distance(int number_of_steps);

void robot_keep_right();

int right_x_pos();

int right_y_pos();

int left_x_pos();

int left_y_pos();

void set_coordinate_in_array(int y, int x, int value);

void save_detected_walls_in_array();

bool drive_nearest_path();

bool detect_path(int next_yposition,int next_xposition);

void nearest_path_to_array();

#endif /* SEARCHANDFINDGURRA_H_ */