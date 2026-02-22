#ifndef TIC_H
#define TIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
//#include <conio.h> // Im not using this yet
// I should add proper error checking... with errno.h - perror()

#ifdef _WIN32
    #include <conio.h>  // Use the native Windows library
#else
    #include "posix_input.h" // Use our custom UNIX definition for Windows equivalent functions
#endif

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_XOFFSET 12
#define BOARD_YOFFSET 9

#define COLOR_COMPLEXITY 9
#define COLOR_AMOUNT 7

#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

#define ANSI_COLOR_BLACK_BG   "\x1b[40m"
#define ANSI_COLOR_RED_BG     "\x1b[41m"
#define ANSI_COLOR_GREEN_BG   "\x1b[42m"
#define ANSI_COLOR_YELLOW_BG  "\x1b[43m"
#define ANSI_COLOR_BLUE_BG    "\x1b[44m"
#define ANSI_COLOR_MAGENTA_BG "\x1b[45m"
#define ANSI_COLOR_CYAN_BG    "\x1b[46m"
#define ANSI_COLOR_WHITE_BG   "\x1b[47m"

#define ANSI_COLOR_BLACK_BRIGHT   "\x1b[90m"
#define ANSI_COLOR_RED_BRIGHT     "\x1b[91m"
#define ANSI_COLOR_GREEN_BRIGHT   "\x1b[92m"
#define ANSI_COLOR_YELLOW_BRIGHT  "\x1b[93m"
#define ANSI_COLOR_BLUE_BRIGHT    "\x1b[94m"
#define ANSI_COLOR_MAGENTA_BRIGHT "\x1b[95m"
#define ANSI_COLOR_CYAN_BRIGHT    "\x1b[96m"
#define ANSI_COLOR_WHITE_BRIGHT   "\x1b[97m"

#define ANSI_COLOR_BLACK_BRIGHT_BG   "\x1b[100m"
#define ANSI_COLOR_RED_BRIGHT_BG     "\x1b[101m"
#define ANSI_COLOR_GREEN_BRIGHT_BG   "\x1b[102m"
#define ANSI_COLOR_YELLOW_BRIGHT_BG  "\x1b[103m"
#define ANSI_COLOR_BLUE_BRIGHT_BG    "\x1b[104m"
#define ANSI_COLOR_MAGENTA_BRIGHT_BG "\x1b[105m"
#define ANSI_COLOR_CYAN_BRIGHT_BG    "\x1b[106m"
#define ANSI_COLOR_WHITE_BRIGHT_BG   "\x1b[107m"

typedef struct Colors{
	char color_list[COLOR_COMPLEXITY][COLOR_AMOUNT];
	char normal[COLOR_COMPLEXITY][COLOR_AMOUNT];
	char bright[COLOR_COMPLEXITY][COLOR_AMOUNT];
	char background[COLOR_COMPLEXITY][COLOR_AMOUNT];
	char bright_background[COLOR_COMPLEXITY][COLOR_AMOUNT];
}Colors;

typedef struct Player{
	char default_color[COLOR_COMPLEXITY];
	char color[COLOR_COMPLEXITY];

	char *character;
	int *wins;
}Player;

typedef struct Board{
	short *x_pos;
	short *y_pos;

	int *width;
	int *height;

	char board[BOARD_HEIGHT][BOARD_WIDTH];

	char *turn;
	char *target;
	char *space;
	char *color_type;	

	char boarder_color[COLOR_COMPLEXITY];
	char space_color[COLOR_COMPLEXITY];
	char turn_color[COLOR_COMPLEXITY];
	char pending_color[COLOR_COMPLEXITY];

	bool *session;

	Colors *ANSI;
}Board;


/*
Name: 
	initialize_colors
Purpose:
	Initializes, allocates, defines and sets the color struct.
Parameters:
	void
Returns: 
	typedef struct Colors* ~ a struct containing a list of each color type.
*/
Colors* initialize_colors();

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
void create_stage(Board *game_sourse);

/*
Name: 
	print_to_terminal
Purpose:
	Prints the board to the screen.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void print_to_terminal(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	handle_input
Purpose:
	Functionally gathers and uses inputs from the user.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
	input (char) ~ The gatherd input of the user.
Returns:
	void
*/
void handle_input(Board *game_sourse, Player *p1, Player *p2, char input);

/*
Name: 
	select_square
Purpose:
	Selectes the space the user desires and alternates turns.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	char ~ the current_piece and selection chosen by the user.
*/
void select_square(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	game_state
Purpose:
	Gets games end state Tie or Win then prints out the cooresponding result. 
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void game_state(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	end_logic
Purpose:
	Checks to see if any wins or ties have accrued and validates them. 
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	char ~ T or W representing win or tie.
*/
char end_logic(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	change_input
Purpose:
	Replaces previous piece sets with new user given characters 
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
	input (char) ~ The gatherd input of the user.
Returns:
	void
*/
void change_input(Board *game_sourse, Player *p1, Player *p2, char input);

/*
Name: 
	change_character_color
Purpose:
	Picks and replace colors of playable targets.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	char* ~ The given color.
*/
void change_character_color(Board *game_sourse, Player *p1, Player *p2);

void change_color(Board *game_sourse, Player *p1, Player *p2, char target, char *label);

/*
Name: 
	color_validification
Purpose:
	Checks if color is valid (is in list of colors)
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	color (char*) ~ the set color given by the user.
	chosen_color (char*) ~ the target color.
Returns:
	char* ~ The valid color.
*/
char* color_validification(Board *game_sourse, char *color, char *chosen_color);

/*
Name: 
	change_stage
Purpose:
	Lists Setting changes to the user and inputs the changes.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void change_stage(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	color_input
Purpose:
	Comparse a valid input then send back the color in ANSI form.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	color (char*) ~ Valid input from user.
Returns:
	char* ~ Valid color in ANSI form.
*/
char* color_input(Board *game_sourse, char *color);

/*
Name: 
	change_spaces
Purpose:
	Changes the character representing the spaces to an input.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void change_spaces(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	free_memory
Purpose:
	Frees all allocated memory structs.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void free_memory(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	exit_game
Purpose:
	Clears all tasks and Exits the Game.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void exit_game(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	help_control
Purpose:
	Helps the user understand the game and its controls
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void help_control(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	change_color_types
Purpose:
	Changes every changeable to its proper type.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void change_color_types(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	aspect_change
Purpose:
	Gets the index of the original color.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	target (char*) ~ The original color.
Returns:
	char* ~ The same color as the new type.
*/
char* aspect_change(Board *game_sourse, char* target);

/*
Name: 
	color_parse
Purpose:
	Changes the color to its proper color type.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	index (int) ~ The index of the color in color list.
Returns:
	char* ~ The same color as the new type.
*/
char* color_parse(Board *game_sourse, int index);

/*
Name: 
	change_all_color
Purpose:
	changes all of the changeable color values.
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
Returns:
	void
*/
void change_all_color(Board *game_sourse, Player *p1, Player *p2);

/*
Name: 
	safe_input
Purpose:
	gets a valid input excluding values or including values depending on the domain. 
Parameters:
	game_sourse (typedef Struct Board*) ~ Holds all related feild to the board.
	p1 (typedef Struct Player*) ~ Holds all related feild to the player one.
	p2 (typedef Struct Player*) ~ Holds all related feild to the player two.
	domain (char) ~ Tells the funciton if it will include or exclude the following values as inputs.
	count (int) ~ The amount of following arguments.
Returns:
	char ~ The original input.
*/
char safe_input(Board *game_sourse, Player *p1, Player *p2, char domain, int count, ...);

// Leave 14 rows empty in the terminal (ctrl + shift + p {input} Terminal: Set Fixed Dimensions {input}\n {input} 14)

#endif