#include "tic.h"

int main(void)
{
	// Set default characters //
    char set_right_box = 'O';
    char set_left_box = 'X';
	char set_space = '#';
	char color_version = 'A';
	
	// Set default player one //
	char turn = set_left_box;

	// Set default win amount //
	int X_wins = 0;
	int O_wins = 0;

	// Define uninitialized variables //
	char color_target;
	char input;

	// Set Board Paramaters //
	int game_width = BOARD_WIDTH;
	int game_height = BOARD_HEIGHT;
	bool game_in_session = true;

	// Set starting values //
	short pos_x = 1;
	short pos_y = 2;
	
	// Memory allocation //
	Board *game = malloc(sizeof(Board));
	Player *player_1 = malloc(sizeof(Player));
	Player *player_2 = malloc(sizeof(Player));
	if (game == NULL || player_1 == NULL || player_2 == NULL) return 1; // Check allocation status

	// Set game default pointers //
	strncpy(game->boarder_color, ANSI_COLOR_WHITE, COLOR_COMPLEXITY);
	strncpy(game->space_color, ANSI_COLOR_WHITE, COLOR_COMPLEXITY);	
	strncpy(game->turn_color, ANSI_COLOR_GREEN, COLOR_COMPLEXITY);
	strncpy(game->pending_color, ANSI_COLOR_WHITE, COLOR_COMPLEXITY);	
	game->x_pos = &pos_x;
	game->y_pos = &pos_y;
	game->width = &game_width;
	game->height = &game_height;
	game->turn = &turn;
	game->target = &color_target;
	game->session = &game_in_session;
	game->space = &set_space;
	game->color_type = &color_version;

	// Set player one default pointers //
	strncpy(player_1->default_color, ANSI_COLOR_RED, COLOR_COMPLEXITY);
	strncpy(player_1->color, ANSI_COLOR_RED, COLOR_COMPLEXITY);
	player_1->character = &set_left_box;
	player_1->wins = &X_wins;

	// Set player two default pointers //
	strncpy(player_2->default_color, ANSI_COLOR_BLUE, COLOR_COMPLEXITY);
	strncpy(player_2->color, ANSI_COLOR_BLUE, COLOR_COMPLEXITY);
	player_2->character = &set_right_box;
	player_2->wins = &O_wins;

	game->ANSI = initialize_colors();

	// Initialize Board //
	create_stage(game);

	// Output //
	print_to_terminal(game, player_1, player_2);

	// Sets position on the board //
    printf("\033[11;14H");

	// Eventlistener for keys //
	while (1) {
		input = getch();
		handle_input(game, player_1, player_2, input); // handles all other inputs
		if (input == 'q') exit_game(game, player_1, player_2); // Quit game
		if (input == 'L') change_input(game, player_1, player_2, input); // change player 1 character
		if (input == 'R') change_input(game, player_1, player_2, input); // change player 2 character
		if (input == 'C') change_character_color(game, player_1, player_2); // change color
		if (input == 'M') change_stage(game, player_1, player_2); // Change the stage
		if (input == 'H') help_control(game, player_1, player_2); // Provides a list of information
	}
}