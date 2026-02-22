#include "tic.h"

char end_logic(Board *game_sourse, Player *p1, Player *p2) {
    int tag_count = 0;
    for (int j = 0; j < *game_sourse->height; j++) {
    // initializes all of the winning checks //
    int check_O_row = 0;
    int check_X_row = 0;
    int check_O_col = 0;
    int check_X_col = 0;
    int check_X_dia = 0;
    int check_O_dia = 0;
    int check_X_bia = 0;
    int check_O_bia = 0;
    int smaller = (*game_sourse->width > *game_sourse->height) ? *game_sourse->height : *game_sourse->width;

        for (int i = 0; i < *game_sourse->width; i++) {
            
            if (game_sourse->board[i][j] != *game_sourse->space) tag_count++; // Counts all empty spaces
            
            // Counts each check case //
            if (game_sourse->board[i][j] == *p1->character) check_X_col++; // X column
            if (game_sourse->board[j][i] == *p1->character) check_X_row++; // X row
            if (game_sourse->board[i][j] == *p2->character) check_O_col++; // O column
            if (game_sourse->board[j][i] == *p2->character) check_O_row++; // O row
            if (game_sourse->board[i][*game_sourse->width-1-i] == *p1->character) check_X_bia++; // X bottom diagonal
            if (game_sourse->board[i][i] == *p1->character) check_X_dia++; // X top diagonal
            if (game_sourse->board[i][*game_sourse->width-1-i] == *p2->character) check_O_bia++; // O bottom diagonal
            if (game_sourse->board[i][i] == *p2->character) check_O_dia++; // O top diagonal

            // Validates victory //
            if (check_X_col == *game_sourse->height || check_X_row == *game_sourse->width || 
                check_O_col == *game_sourse->height || check_O_row == *game_sourse->width ||
                check_X_dia == smaller || check_O_dia == smaller ||
                check_X_bia == smaller || check_O_bia == smaller)
                return 'W';
                
            // Checks for Ties //
            if (tag_count == *game_sourse->width**game_sourse->height)
                return 'T';
        }
    }
    return '\0';
}

void game_state(Board *game_sourse, Player *p1, Player *p2) {

    // Checks If Game has been won //
    char game_status = end_logic(game_sourse, p1, p2);

    // Checks for Wins or Draws //
    if (game_status == 'W') {
        // Sets cursor position to top of the page //
        printf("\033[8;12H");
        // Displays Winning Text //
        printf("%c WINS", (*game_sourse->turn == *p1->character) ? *p2->character:*p1->character);

        // incriments the wins of each player //
        if (*game_sourse->turn == *p2->character) *p1->wins = *p1->wins + 1;
        if (*game_sourse->turn == *p1->character) *p2->wins = *p2->wins + 1;

    } else if (game_status == 'T') {
        // Sets cursor position to top of the page //
        printf("\033[8;13H");
        // Displays Draw text //
        printf("Tie");
    }

    if (game_status == 'T' || game_status == 'W') {
        // Moves cursor to bottome of the page //
        printf("\033[16;4H");
        // Displays New game Text //
        printf("Click N for new Game!");
        // Ends the session //
        *game_sourse->session = false;
    }
    
}

void free_memory(Board *game_sourse, Player *p1, Player *p2) {
    
    free(game_sourse->ANSI); // Color struct
    game_sourse->ANSI = NULL;

	free(game_sourse); // Board struct
	game_sourse = NULL;

	free(p1); // Player struct
	p1 = NULL;

	free(p2); // Player struct
	p2 = NULL;
}

void exit_game(Board *game_sourse, Player *p1, Player *p2) {
	free_memory(game_sourse, p1, p2); // Free memeory and set pointer to NULL
	printf("\033[16;14H"); // Moves to the bottem of the screen
	exit(0); // exits the game 
}