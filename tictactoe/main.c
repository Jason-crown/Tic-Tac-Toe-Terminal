#include "tic.h"

int main(void)
{
	Player player_1 = {ANSI_COLOR_RED, ANSI_COLOR_RED, 'X', 0};
	// Initialize Board //
	char board[BOARD_HEIGHT][BOARD_WIDTH];
	create_stage(board);

	// setting letters //
    char set_right_box = 'O';
    char set_left_box = 'X';
	char turn = set_left_box;
	int X_wins = 0;
	int O_wins = 0;
	char *color;
	char color_target;
	bool game_in_session = true;

	// Output //
	print_to_terminal(board, set_right_box, set_left_box, &turn, &X_wins, &O_wins, &game_in_session, color, &color_target);

	// Sets position on the board //
    printf("\033[11;14H");

	// initialize changing pointer //
	char input;
	short pos_x = 1;
	short pos_y = 2;
	char current_piece;


	// Eventlistener for keys //
	while (1) {
		input = getch();
		handle_input(board, &pos_x, &pos_y, input, &current_piece, set_right_box, set_left_box, &turn, &X_wins, &O_wins, &game_in_session, color, &color_target);

		// Quit game //
		if (input == 'q') {
			// moves to the bottem of the screen //
			printf("\033[16;14H");
			// exits the game //
			exit(0);
		}

		// change character //
		if (input == 'L') {
			change_input(board, input, &set_left_box, &set_right_box, &turn);
		}
		if (input == 'R') {
			change_input(board, input, &set_right_box, &set_left_box, &turn);
		}

		// change color //
		if (input == 'C') {
			printf("\033[17;5H");
			printf("choose which player \n       (%c or %c) : ", set_left_box, set_right_box);
			color_change(color, set_left_box, set_right_box, &color_target);
			print_to_terminal(board, set_right_box, set_left_box, &turn, &X_wins, &O_wins, &game_in_session, color, &color_target);
			printf("\033[11;14H");
		}
	}
}



