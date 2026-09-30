#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#ifdef _WIN32
    #include <conio.h>  // Use the native Windows library
#else
    #include "posix_input.h" // Use our custom UNIX definition for Windows equivalent functions
#endif

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_XOFFSET 12
#define BOARD_YOFFSET 9

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
	char default_color[8];
	char color[8];
	char character;
	int wins;
}Player;

/*
Name: 
	create_stage
Purpose:
	Sets up the physical layout of the board. 
Parameters:
	board (char[][]) ~ The board of the pieces and their indices. 
Returns: 
	void
*/
void create_stage(char board[BOARD_HEIGHT][BOARD_WIDTH]);

/*
Name: 
	print_to_terminal
Purpose:
	Prints the board to the screen.
Parameters:
	board (char[][]) ~ The board of the pieces and their indices.
	set_right_box (char) ~ The player two on the board's character.
	set_left_box (char) ~ The player one on the board's character.
	turn (char*) ~ The turn of the set player. 
	game_in_session (bool*) ~ Checks if the game is still active.
	X_wins (int*) ~ The amount of wins player one has.
	O_wins (int*) ~ The amount of wins player two has.
	color (char*) ~ the set color given by the user.
	color_target (char*) ~ the target of the color change.
Returns:
	void
*/
void print_to_terminal(char board[BOARD_HEIGHT][BOARD_WIDTH], char set_right_box, char set_left_box, char* turn, int* X_wins, int* O_wins, bool* game_in_session, char* color, char* color_target);

/*
Name: 
	handle_input
Purpose:
	functionally gathers and uses inputs from the user.
Parameters:
	board (char[][]) ~ The board of the pieces and their indices.
	pos_x (short*) ~ The relitive x position.
	pos_y (short*) ~ The relitive y position.
	input (char) ~ The gatherd input of the user.
	current_piece (char*) ~ The selected placement chosen by the user.
	turn (char*) ~ The turn of the set player.
	set_right_box (char) ~ The player two on the board's character.
	set_left_box (char) ~ The player one on the board's character.
	turn (char*) ~ The turn of the set player. 
	X_wins (int*) ~ The amount of wins player one has.
	O_wins (int*) ~ The amount of wins player two has.
	game_in_session (bool*) ~ Checks if the game is still active.
	color (char*) ~ the set color given by the user.
	color_target (char*) ~ the target of the color change.
Returns:
	void
*/
void handle_input(char board[BOARD_HEIGHT][BOARD_WIDTH], short* pos_x, short* pos_y, char input, char* current_piece, char set_right_box, char set_left_box, char* turn, int* X_wins, int* O_wins, bool* game_in_session, char* color, char* color_target);

/*
Name: 
	select_square
Purpose:
	Selectes the space the user desires and alternates turns.
Parameters:
	board (char[][]) ~ The board of the pieces and their indices.
	pos_x (short*) ~ The relitive x position.
	pos_y (short*) ~ The relitive y position.
	current_piece (char*) ~ The selected placement chosen by the user.
	set_right_box (char) ~ The player two on the board's character.
	set_left_box (char) ~ The player one on the board's character.
	turn (char*) ~ The turn of the set player.
Returns:
	char ~ the current_piece and selection chosen by the user.
*/
char select_square(char board[BOARD_HEIGHT][BOARD_WIDTH], short pos_x, short pos_y, char* current_piece, char set_right_box, char set_left_box, char* turn);

/*
Name: 
	game_state
Purpose:
	Gets games end state Tie or Win then prints out the cooresponding result. 
Parameters:
	board (char[][]) ~ The board of the pieces and their indices.
	set_right_box (char) ~ The player two on the board's character.
	set_left_box (char) ~ The player one on the board's character.
	turn (char*) ~ The turn of the set player.
	X_wins (int*) ~ The amount of wins player one has.
	O_wins (int*) ~ The amount of wins player two has.
	game_in_session (bool*) ~ Checks if the game is still active.
Returns:
	void
*/
void game_state(char board[BOARD_HEIGHT][BOARD_WIDTH], char set_right_box, char set_left_box, char* turn, int* X_wins, int* O_wins, bool* game_in_session);

/*
Name: 
	end_logic
Purpose:
	Checks to see if any wins or ties have accrued and validates them. 
Parameters:
	board (char[][]) ~ The board of the pieces and their indices.
	set_right_box (char) ~ The player two on the board's character.
	set_left_box (char) ~ The player one on the board's character.
Returns:
	char ~ T or W representing win or tie.
*/
char end_logic(char board[BOARD_WIDTH][BOARD_HEIGHT], char set_right_box, char set_left_box);

/*
Name: 
	change_input
Purpose:
	Replaces previous piece sets with new user given characters 
Parameters:
	board (char[][]) ~ The board of the pieces and their indices.
	input (char) ~ The gatherd input of the user.
	set_box (char*) ~ The player on the board's character.
	unset_box (char*) ~ The other player on the board's character.
	turn (char*) ~ The turn of the set player.
Returns:
	void
*/
void change_input(char board[BOARD_HEIGHT][BOARD_WIDTH], char input, char *set_box, char *unset_box, char* turn);

/*
Name: 
	color_change
Purpose:
	Picks and replace colors of playable targets.
Parameters:
	color (char*) ~ the set color given by the user.
	set_right_box (char) ~ The player two on the board's character.
	set_left_box (char) ~ The player one on the board's character.
	color_target (char*) ~ the target of the color change.
Returns:
	char* ~ The given color.
*/
char* color_change(char *color, char set_left_box, char set_right_box, char *color_target);

/*
Name: 
	color_validification
Purpose:
	Checks if color is valid (is in list of colors)
Parameters:
	color (char*) ~ the set color given by the user.
	chosen_color (char*) ~ the target color.
Returns:
	char* ~ The valid color.
*/
char* color_validification(char *color, char *chosen_color);


#endif