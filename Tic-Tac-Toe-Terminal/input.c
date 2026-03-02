#include "tic.h"

void handle_input(Board *game_sourse, Player *p1, Player *p2, char input)
{
    
    // Board Movement //
    switch (input)
    {
    // Move left //
    case 'a': 
    case 'A':
        (*game_sourse->x_pos)--;
        if (*game_sourse->x_pos < 0) *game_sourse->x_pos = 0;
        break;
    // Move right //
    case 'd':
    case 'D':
        (*game_sourse->x_pos)++;
        if (*game_sourse->x_pos > *game_sourse->width - 1) *game_sourse->x_pos = *game_sourse->width - 1;
        break;
    // Move Down //
    case 's':
    case 'S':
        (*game_sourse->y_pos)++;
        if (*game_sourse->y_pos > *game_sourse->height) *game_sourse->y_pos = *game_sourse->height;
        break;
    // Move Up //
    case 'w':
    case 'W':
        (*game_sourse->y_pos)--;
        if (*game_sourse->y_pos < 1) *game_sourse->y_pos = 1;
        break;
    // Clears Board //
    case 'n':
    case 'N':
        create_stage(game_sourse);
        printf("\033[11;14H");
        *game_sourse->session = true; 
        print_to_terminal(game_sourse, p1, p2);    
        break;
    // Select and Place //
    case '\r':
        if (*game_sourse->session) {
        select_square(game_sourse, p1, p2);
        game_state(game_sourse, p1, p2);
        }
        break;
    }
    // Sets cursor to Saved Position //*/
    //printf("\033[%d;%dH", BOARD_YOFFSET + (*pos_y), BOARD_XOFFSET + ((*pos_x)*2));
    printf("\033[%d;%dH", BOARD_YOFFSET + (*game_sourse->y_pos), BOARD_XOFFSET + ((*game_sourse->x_pos)*2));
    
}

void change_input(Board *game_sourse, Player *p1, Player *p2, char input) {
    char not_target;
    
    // moves cursor to turn feilds //
	printf("\033[11;%dH", (input == 'L') ? 6:22);

    
    if (input == 'L') {
        *game_sourse->target = *p1->character;
        not_target = *p2->character;        
    }

    if (input == 'R') {
        *game_sourse->target = *p2->character;
        not_target = *p1->character;
    }

	char new_set = safe_input(game_sourse, p1, p2, 'N', 8, *game_sourse->space, not_target, '\0', '\b', '\t', '\r', '\n', '\033');
    printf("%c", new_set);

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < *game_sourse->width; x++) {
            if (game_sourse->board[x][y] == *game_sourse->target) game_sourse->board[x][y] = new_set;
        }
    }
    if (*game_sourse->target == *p1->character) {
        *p1->character = new_set;
        *p2->character = not_target;
    }
    if (*game_sourse->target == *p2->character) {
        *p2->character = new_set;
        *p1->character = not_target;
    }

    if (*game_sourse->turn == *game_sourse->target) *game_sourse->turn = new_set;
    *game_sourse->target = new_set;
    print_to_terminal(game_sourse, p1, p2);
    printf("\033[%d;%dH", BOARD_YOFFSET + (*game_sourse->y_pos), BOARD_XOFFSET + ((*game_sourse->x_pos)*2));
}

void select_square(Board *game_sourse, Player *p1, Player *p2) {
    char selected_piece = game_sourse->board[*game_sourse->y_pos - 1][*game_sourse->x_pos];
    // Alternates turns, saves moves, validates choices //
    if (selected_piece != *p1->character && selected_piece != *p2->character) {
        game_sourse->board[*game_sourse->y_pos - 1][*game_sourse->x_pos] = *game_sourse->turn;
        *game_sourse->turn = (*game_sourse->turn == *p1->character) ? *p2->character:*p1->character;
        print_to_terminal(game_sourse, p1, p2);
    }
}

void change_stage(Board *game_sourse, Player *p1, Player *p2) {
    printf("\033[17;7H");
    printf("Stage Settings: \n (X) Color types   (U) Pending Color \n (C) Space Color   (B) Boarder Color \n (T) Turn Color (O) Space characters \n Choice:");
    char setting = getch();
    if (setting == 'X' || setting == 'O' || setting == 'C' || setting == 'B' || setting == 'T' || setting == 'U') {
        printf("%c\n", setting);
        if (setting == 'X') change_color_types(game_sourse, p1, p2); // changes color type on the board
        if (setting == 'O') change_spaces(game_sourse, p1, p2); // changes the spacing character
        if (setting == 'C') change_color(game_sourse, p1, p2, *game_sourse->space, "Board space"); // changes the spacing color
        if (setting == 'B') change_color(game_sourse, p1, p2, '\0', "Game boarder"); // changes the boarder color
        if (setting == 'T') change_color(game_sourse, p1, p2, '\0', "Turn boarder"); // changes the turn boarder color
        if (setting == 'U') change_color(game_sourse, p1, p2, '\0', "Pending boarder"); // changes the turn boarder color
    }
    print_to_terminal(game_sourse, p1, p2);
    printf("\033[%d;%dH", BOARD_YOFFSET + (*game_sourse->y_pos), BOARD_XOFFSET + ((*game_sourse->x_pos)*2));
}

void change_spaces(Board *game_sourse, Player *p1, Player *p2) {
    printf("Input the spacing character: ");
    char new_space = safe_input(game_sourse, p1, p2, 'E', 8, *p1->character, *p2->character, '\b', '\n', '\r', '\t', '\0', '\033');
    for (int i = 0; i < *game_sourse->width; i++) {
        for (int j = 0; j < *game_sourse->height; j++) {
            if (game_sourse->board[i][j] == *game_sourse->space)
            game_sourse->board[i][j] = new_space;
        }
    }
    *game_sourse->space = new_space;
}

char safe_input(Board *game_sourse, Player *p1, Player *p2, char domain, int count, ...) {
    // the domains are (I - Inclusive, E - Exclusive, N - No print Exclusive) //
    bool valid_input;
    char new_input;
    va_list args;
    
    do {
        va_start(args, count);

        new_input = getch();
        if (new_input == 'q') exit_game(game_sourse, p1, p2);  

        for (int i = 0; i < count; i++) {
            if (new_input == (char)va_arg(args, int)) {
                valid_input = (domain == 'I') ? true : false;
                break;
            }
            valid_input = (domain == 'I') ? false : true;
        }

        if (domain == 'I') printf ("%c", new_input);
        if (!valid_input && domain != 'N') printf("\nInvalid : ");

        va_end(args);
    } while (!valid_input);
    return new_input;
}