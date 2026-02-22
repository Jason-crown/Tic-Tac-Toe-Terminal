#include "tic.h"

void create_stage(Board *game_sourse)
{
    char board_cache[*game_sourse->width][*game_sourse->height];
    for (int i = 0; i < *game_sourse->width; i++) {
        for (int j = 0; j < *game_sourse->height; j++) {
            board_cache[i][j] = *game_sourse->space;
        }
    }
    memcpy(game_sourse->board, board_cache, sizeof(char)*(BOARD_HEIGHT * BOARD_WIDTH));
}

void print_to_terminal(Board *game_sourse, Player *p1, Player *p2)
{  

    char p1_color[COLOR_COMPLEXITY];
    char p2_color[COLOR_COMPLEXITY];

    char game_board_color[COLOR_COMPLEXITY];
    char game_space_color[COLOR_COMPLEXITY];

    strncpy(p1_color, p1->color, COLOR_COMPLEXITY);
    strncpy(p2_color, p2->color, COLOR_COMPLEXITY);

    strncpy(game_board_color, game_sourse->boarder_color, COLOR_COMPLEXITY);
    strncpy(game_space_color, game_sourse->space_color, COLOR_COMPLEXITY);    

    if (!(*p1->color)) strncpy(p1_color, ANSI_COLOR_RED, COLOR_COMPLEXITY);
    if (!(*p2->color)) strncpy(p2_color, ANSI_COLOR_BLUE, COLOR_COMPLEXITY);

    if (!(*game_sourse->boarder_color)) strncpy(game_board_color, ANSI_COLOR_RESET, COLOR_COMPLEXITY);
    if (!(*game_sourse->space_color)) strncpy(game_space_color, ANSI_COLOR_RESET, COLOR_COMPLEXITY);

    char first_color_set_X[COLOR_COMPLEXITY] = ANSI_COLOR_WHITE;
    char first_color_set_O[COLOR_COMPLEXITY] = ANSI_COLOR_WHITE;
    char lead_color[COLOR_COMPLEXITY] = ANSI_COLOR_MAGENTA;
    char x_box_color[COLOR_COMPLEXITY];
    char o_box_color[COLOR_COMPLEXITY];

    if (*p1->wins > *p2->wins) {
        strncpy(x_box_color, lead_color, COLOR_COMPLEXITY);
        strncpy(o_box_color, first_color_set_O, COLOR_COMPLEXITY);
    } else if (*p1->wins < *p2->wins) {
        strncpy(o_box_color, lead_color, COLOR_COMPLEXITY);
        strncpy(x_box_color, first_color_set_X, COLOR_COMPLEXITY);
    } else {
        strncpy(x_box_color, first_color_set_X, COLOR_COMPLEXITY);
        strncpy(o_box_color, first_color_set_O, COLOR_COMPLEXITY);
    }

    if (*game_sourse->turn == *p1->character){
        strncpy(first_color_set_X, game_sourse->turn_color, COLOR_COMPLEXITY);
        strncpy(first_color_set_O, game_sourse->pending_color, COLOR_COMPLEXITY);
    } else {
        strncpy(first_color_set_O, game_sourse->turn_color, COLOR_COMPLEXITY);
        strncpy(first_color_set_X, game_sourse->pending_color, COLOR_COMPLEXITY);
    }

    printf("\033[2J"); // Clear screen
    printf("\n");
    // Top of the Board //
    if (*p1->wins>9 && *p2->wins>9) {
        printf("    %s%d%s   %s+-------+%s  %s%d%s%s   \n", x_box_color, *p1->wins, first_color_set_X, game_board_color, ANSI_COLOR_RESET, 
                                                            o_box_color, *p2->wins, first_color_set_O, ANSI_COLOR_RESET);
    } else if (*p1->wins>9 && *p2->wins<=9) {
        printf("     %s%d%s  %s+-------+%s   \n", 
                x_box_color, *p1->wins, first_color_set_X, game_board_color, ANSI_COLOR_RESET);
    } else if (*p1->wins<=9 && *p2->wins>9){
        printf("         %s+-------+%s   %d%s%s   \n", 
                game_board_color, o_box_color, *p2->wins, first_color_set_O, ANSI_COLOR_RESET);
    } else if (*p1->wins<=9 && *p2->wins<=9) {
        printf("         %s+-------+%s       \n", game_board_color, ANSI_COLOR_RESET);
    }
    // Iterate Through Grid //
    for (int x = 0; x < *game_sourse->height; x++)
    {
        if (x == 0 || x == 2) {
            
                if (x == 0 && *p1->wins > 0 && *p1->wins<10) {
                    printf("   %s+-%s%d%s%s-+%s %s| %s", first_color_set_X, x_box_color, *p1->wins, ANSI_COLOR_RESET, first_color_set_X, ANSI_COLOR_RESET,game_board_color, ANSI_COLOR_RESET);
                } else {
                    printf("   %s+---+%s %s| %s", first_color_set_X, ANSI_COLOR_RESET, game_board_color, ANSI_COLOR_RESET);   
                } 
            
        } else if (x ==1) {
            printf("   %s|%s", first_color_set_X, ANSI_COLOR_RESET);
            printf("%s %c %s", p1_color, *p1->character, ANSI_COLOR_RESET);
            printf("%s|%s %s| %s", first_color_set_X, ANSI_COLOR_RESET, game_board_color, ANSI_COLOR_RESET);
        }
        // Print Columns //
        for (int y = 0; y < *game_sourse->width; y++) {
            
            if (game_sourse->board[x][y] == *p1->character) {
                printf("%s%c%s" , p1_color, game_sourse->board[x][y], ANSI_COLOR_RESET);
            }else if (game_sourse->board[x][y] == *p2->character) {
                printf("%s%c%s", p2_color, game_sourse->board[x][y], ANSI_COLOR_RESET);
            } else if (game_sourse->board[x][y] == *game_sourse->space) {
                printf("%s%c%s", game_space_color, game_sourse->board[x][y], ANSI_COLOR_RESET);  
            } else {
                printf("%c", game_sourse->board[x][y]); 
            }
            printf("%s ", game_board_color);
            
        }

        if (x == 0 || x== 2) { 
            
                if (x == 0 && *p2->wins > 0 && *p2->wins<10) {
                    printf("%s|%s %s+-%s%d%s%s-+%s  \n", game_board_color, ANSI_COLOR_RESET, first_color_set_O, o_box_color, *p2->wins, ANSI_COLOR_RESET, first_color_set_O, ANSI_COLOR_RESET);
                }else {
                    printf("%s|%s %s+---+%s  \n", game_board_color, ANSI_COLOR_RESET, first_color_set_O, ANSI_COLOR_RESET);
                }
            
        } else if ( x == 1 ) { 
            printf("%s|%s %s|%s", game_board_color, ANSI_COLOR_RESET, first_color_set_O, ANSI_COLOR_RESET);
            printf("%s %c %s", p2_color, *p2->character, ANSI_COLOR_RESET);
            printf("%s|%s \n", first_color_set_O, ANSI_COLOR_RESET);
        }
    }

    // Bottom of the Board //
    printf("         %s+-------+%s       \n", game_board_color, ANSI_COLOR_RESET);

    // Important tools //
    printf("\033[2;0H");
    printf("Quit->(q)         Help->(H)");
    printf("\033[");

    if (!(*game_sourse->session)) {
        // Moves cursor to bottome of the page //
        printf("\033[16;4H");
        // Displays New game Text //
        printf("Click N for new Game!");
    }
}

void help_control(Board *game_sourse, Player *p1, Player *p2) {
	printf("\033[2J"); 
	printf("       %sW%se%sl%sc%so%sm%se %s!!\n", 
        ANSI_COLOR_RED_BRIGHT, ANSI_COLOR_YELLOW_BRIGHT, ANSI_COLOR_GREEN_BRIGHT, ANSI_COLOR_BLUE_BRIGHT, 
        ANSI_COLOR_CYAN_BRIGHT, ANSI_COLOR_MAGENTA_BRIGHT, ANSI_COLOR_WHITE_BRIGHT, ANSI_COLOR_RESET);
	printf("\n                   Description:");
	printf("\n %sThis is a Tic-tac-toe game made in the C terminal", ANSI_COLOR_MAGENTA_BRIGHT);
	printf("\n%sAttempt to make a contiguous connection of 3 peices.", ANSI_COLOR_GREEN_BRIGHT);
	printf("\n                     Controls:");
	printf("\n%s (R and L) Is to change the character of the peices.", ANSI_COLOR_RED_BRIGHT);
	printf("\n (C) Is to change the colors of the peices.");
	printf("\n (Enter) is to play your peice.");
	printf("\n (M) moves you to the menu.");
	printf("\n (Q) Quits the Game.");	
	printf("\n%s Note: Set the terminal to '14 rows empty'.\n", ANSI_COLOR_CYAN_BRIGHT);
	printf(" %sCLick anything to get back to the game.%s", ANSI_COLOR_BLUE_BRIGHT, ANSI_COLOR_RESET);	
    char input = getch();
    if (input == 'q') exit_game(game_sourse, p1, p2);
	if (input) print_to_terminal(game_sourse, p1, p2);
	printf("\033[%d;%dH", BOARD_YOFFSET + (*game_sourse->y_pos), BOARD_XOFFSET + ((*game_sourse->x_pos)*2));
}
