#include "tic.h"

void handle_input(char board[BOARD_HEIGHT][BOARD_WIDTH], short* pos_x, short* pos_y, char input, char* current_piece, char set_right_box, char set_left_box, char* turn, int* X_wins, int* O_wins, bool* game_in_session, char* color, char *color_target)
{
    // Board Movement //
    switch (input)
    {
    // Move left //
    case 'a': 
    case 'A':
        (*pos_x)--;
        if (*pos_x < 0) *pos_x = 0;
        break;
    // Move right //
    case 'd':
    case 'D':
        (*pos_x)++;
        if (*pos_x > BOARD_WIDTH - 1) *pos_x = BOARD_WIDTH - 1;
        break;
    // Move Down //
    case 's':
    case 'S':
        (*pos_y)++;
        if (*pos_y > BOARD_HEIGHT) *pos_y = BOARD_HEIGHT;
        break;
    // Move Up //
    case 'w':
    case 'W':
        (*pos_y)--;
        if (*pos_y < 1) *pos_y = 1;
        break;
    // Clears Board //
    case 'n':
    case 'N':
        create_stage(board);
        printf("\033[11;14H");
        *game_in_session = true; 
        print_to_terminal(board, set_right_box, set_left_box, turn, X_wins, O_wins, game_in_session, color, color_target);    
          
        break;
    // Select and Place //
    case '\r':
        if (*game_in_session){
        *current_piece = select_square(board, *pos_x, *pos_y, current_piece, set_right_box, set_left_box, turn);
        print_to_terminal(board, set_right_box, set_left_box, turn, X_wins, O_wins, game_in_session, color, color_target);
        game_state(board, set_right_box, set_left_box, turn, X_wins, O_wins, game_in_session);
        }
        break;
    }
    // Sets cursor to Saved Position //
    printf("\033[%d;%dH", BOARD_YOFFSET + (*pos_y), BOARD_XOFFSET + ((*pos_x)*2));
}

void change_input(char board[BOARD_HEIGHT][BOARD_WIDTH], char input, char *set_box, char *unset_box, char* turn) {
    // moves cursor to turn feilds //
	printf("\033[11;%dH", (input == 'L') ? 6:22);
	char new_set = getch();
    // prevents duplicat indices //
    if (new_set == '#' || new_set == *unset_box) {
        new_set = getch();
    } else {
        // sets new character and filters the board //
        printf("%c", new_set);
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            for (int x = 0; x < BOARD_WIDTH; x++) {
                if (board[x][y] == *set_box)
                    board[x][y] = new_set;
            }
        }			
        if (*turn == *set_box) 
            *turn = new_set;
        *set_box = new_set;
        printf("\033[11;14H");
    }
}