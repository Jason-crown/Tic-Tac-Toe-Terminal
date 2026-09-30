#include "tic.h"

char end_logic(char board[BOARD_WIDTH][BOARD_HEIGHT], char set_right_box, char set_left_box) {
    int tag_count = 0;
    for (int j = 0; j < BOARD_HEIGHT; j++) {
    // initializes all of the winning checks //
    int check_O_row = 0;
    int check_X_row = 0;
    int check_O_col = 0;
    int check_X_col = 0;
    int check_X_dia = 0;
    int check_O_dia = 0;
    int check_X_bia = 0;
    int check_O_bia = 0;

        for (int i = 0; i < BOARD_WIDTH; i++) {
            // Counts all non X or O spaces //
            if (board[i][j] != '#')
                tag_count++;

            // Counts each check case //
            if(board[i][j] == set_left_box) // X column
                check_X_col++;

            if(board[j][i] == set_left_box) // X row
                check_X_row++;

            if(board[i][j] == set_right_box) // O column
                check_O_col++;

            if(board[j][i] == set_right_box) // O row
                check_O_row++;

            if (board[i][BOARD_WIDTH-1-i] == set_left_box) // X bottom diagonal
                check_X_bia++;

            if (board[i][i] == set_left_box) // X top diagonal
                check_X_dia++;

            if (board[i][BOARD_WIDTH-1-i] == set_right_box) // O bottom diagonal
                check_O_bia++;

            if (board[i][i] == set_right_box) // O top diagonal
                check_O_dia++;

            // Validates victory //
            if (check_X_col == BOARD_HEIGHT || 
                check_X_row == BOARD_WIDTH || 
                check_O_col == BOARD_HEIGHT || 
                check_O_row == BOARD_WIDTH ||
                check_X_dia == ((BOARD_WIDTH > BOARD_HEIGHT) ? BOARD_HEIGHT : BOARD_WIDTH)||
                check_O_dia == ((BOARD_WIDTH > BOARD_HEIGHT) ? BOARD_HEIGHT : BOARD_WIDTH) ||
                check_X_bia == ((BOARD_WIDTH > BOARD_HEIGHT) ? BOARD_HEIGHT : BOARD_WIDTH) ||
                check_O_bia == ((BOARD_WIDTH > BOARD_HEIGHT) ? BOARD_HEIGHT : BOARD_WIDTH))
                return 'W';
                
            // Checks for Ties //
            if (tag_count == BOARD_WIDTH*BOARD_HEIGHT)
                return 'T';
        }
    }
}

void game_state(char board[BOARD_HEIGHT][BOARD_WIDTH], char set_right_box, char set_left_box, char* turn, int* X_wins, int* O_wins, bool* game_in_session) {

    // Checks If Game has been won //
    char game_status = end_logic(board, set_right_box, set_left_box);

    // Checks for Wins or Draws //
    if (game_status == 'W') {
        // Sets cursor position to top of the page //
        printf("\033[8;12H");
        // Displays Winning Text //
        printf("%c WINS", (*turn == set_left_box) ? set_right_box:set_left_box);

        // incriments the wins of each player //
        if (*turn == set_right_box) *X_wins = *X_wins + 1;
        if (*turn == set_left_box) *O_wins = *O_wins + 1;

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
        *game_in_session = false;
    }
    
}