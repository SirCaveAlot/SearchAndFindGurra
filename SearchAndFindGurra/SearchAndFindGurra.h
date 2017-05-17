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
extern bool finished_with_drive_nearest_path;
//extern int right_distance;
//extern int left_distance;

void robot_set_direction(int next_direction);

void robot_turn_right();

void robot_turn_left();

void robot_turn_around();

int next_x_position(int);

int next_y_position(int);

bool detect_wall(int next_xposition, int next_yposition);

void robot_move();

void robot_move_distance(int number_of_steps);

void robot_keep_right();

int right_x_pos();

int right_y_pos();

int left_x_pos();

int left_y_pos();

int back_x_pos();

int back_y_pos();

int forward_to_left_x_pos();

int forward_to_left_y_pos();

void set_coordinate_in_array(int y, int x, int value);

void set_coordinate_in_NP_array(int y, int x, int value);

void save_detected_walls_in_array();

void save_detected_outer_wall_in_array();

bool drive_nearest_path();

bool drive_back_nearest_path();

bool detect_path(int next_yposition,int next_xposition, int value);

void drive_to_distressed_and_return();

void nearest_path_to_array();

void robot_detect_outer_walls();

void find_unknown_cells_after_detection_of_outer_walls();

int first_undiscovered_tile_y;

int first_undiscovered_tile_x;

#endif /* SEARCHANDFINDGURRA_H_ */