#include "tic.h"

void create_stage(char board[BOARD_HEIGHT][BOARD_WIDTH])
{
    char board_cache[BOARD_HEIGHT][BOARD_WIDTH] =
    {
        {'#', '#', '#'},
        {'#', '#', '#'},
        {'#', '#', '#'}
    };

    memcpy(board, board_cache, sizeof(char)*(BOARD_HEIGHT * BOARD_WIDTH));
}

void print_to_terminal(char board[BOARD_HEIGHT][BOARD_WIDTH], char set_right_box, char set_left_box, char* turn, int* X_wins, int* O_wins, bool* game_in_session, char* color, char* color_target)
{
    char p1_color[8]= ANSI_COLOR_RED;
    char p2_color[8]= ANSI_COLOR_BLUE;

    if (*color_target == set_left_box) {
        strncpy(p1_color, color, 7);
    } else if (*color_target == set_right_box){
        strncpy(p2_color, color, 7);
    }
        
    char first_color_set_X[8] = ANSI_COLOR_RESET;
    char first_color_set_O[8] = ANSI_COLOR_RESET;
    char lead_color[8] = ANSI_COLOR_MAGENTA;
    char *C = (*turn == set_left_box) ? (strncpy(first_color_set_X, ANSI_COLOR_GREEN, 8),
                                strncpy(first_color_set_O, ANSI_COLOR_RESET, 8)) : (
                                strncpy(first_color_set_O, ANSI_COLOR_GREEN, 8), 
                                strncpy(first_color_set_X, ANSI_COLOR_RESET, 8));

    printf("\033[2J"); // Clear screen
    printf("\n");
    // Top of the Board //
    if (*X_wins>=10) {
        printf("     %s%d%s%s   +-------+   %s%d%s%s   \n", ((*X_wins > *O_wins) ? lead_color : first_color_set_X), *X_wins, first_color_set_X, ANSI_COLOR_RESET, ((*X_wins < *O_wins) ? lead_color : first_color_set_O), *O_wins, first_color_set_O, ANSI_COLOR_RESET);
    } else if (*X_wins<10) {
        printf("         +-------+       \n");
    }
    // Iterate Through Grid //
    for (int x = 0; x < BOARD_HEIGHT; x++)
    {
        if (x == 0 || x == 2) {
            
                if (x == 0 && *X_wins > 0 && *X_wins<10) {
                    printf("   %s+-%s%d%s-+%s | ", first_color_set_X, ((*X_wins > *O_wins) ? lead_color : first_color_set_X), *X_wins, first_color_set_X, ANSI_COLOR_RESET);
                } else {
                    printf("   %s+---+%s | ", first_color_set_X, ANSI_COLOR_RESET);   
                } 
            
        } else if (x ==1) {
            printf("   %s|%s ", first_color_set_X, ANSI_COLOR_RESET);
            printf("%s%c%s", p1_color, set_left_box, ANSI_COLOR_RESET);
            printf(" %s| %s| ", first_color_set_X, ANSI_COLOR_RESET);
        }
        // Print Columns //
        for (int y = 0; y < BOARD_WIDTH; y++) {
            if (board[x][y] == set_left_box) {
                printf( "%s%c%s " , p1_color, board[x][y], ANSI_COLOR_RESET);
            }else if (board[x][y] == set_right_box) {
                printf("%s%c%s ", p2_color, board[x][y],ANSI_COLOR_RESET);
            } else {
                printf("%c ", board[x][y]);  
            }
        }

        if (x == 0 || x== 2) { 
            
                if (x == 0 && *O_wins > 0 && *O_wins<10) {
                    printf("| %s+-%s%d%s-+%s  \n", first_color_set_O, ((*X_wins < *O_wins) ? lead_color : first_color_set_O), *O_wins, first_color_set_O, ANSI_COLOR_RESET);
                }else {
                    printf("| %s+---+%s  \n", first_color_set_O, ANSI_COLOR_RESET);
                }
            
        } else if ( x == 1 ) { 
            printf("| %s|%s ", first_color_set_O, ANSI_COLOR_RESET);
                printf("%s%c%s", p2_color, set_right_box, ANSI_COLOR_RESET);
            printf(" %s| \n", first_color_set_O);
        }
    }
    // Bottom of the Board //
    printf("         +-------+       \n");
    printf("\033[");

    if (!(*game_in_session)) {
        // Moves cursor to bottome of the page //
        printf("\033[16;4H");
        // Displays New game Text //
        printf("Click N for new Game!");
    }

}

char select_square(char board[BOARD_HEIGHT][BOARD_WIDTH], short pos_x, short pos_y, char* current_piece, char set_right_box, char set_left_box, char* turn) {
    pos_y--; // Correct the position to be an index instead
    char selected_piece = board[pos_y][pos_x];
    // Alternates turns, saves moves, validates choices //
    if (selected_piece != set_left_box && selected_piece != set_right_box) {
        board[pos_y][pos_x] = *turn;
        *turn = (*turn == set_left_box) ? set_right_box:set_left_box;
    }
    return selected_piece;
}

char* color_change(char *color, char set_left_box, char set_right_box, char *color_target) {
	char side = getch();
	char color_hash[8];
	if (side == 'q') exit(1);
	// determine the player //
	if (side == set_left_box || side == set_right_box) {

		printf ("%c", side);

		*color_target = side;
		char chosen_color[7];

		// Collects color form the user //
		do {
			printf("\n input the color you want for %c \n color : ", side);
			if(fgets(color_hash, sizeof(color_hash), stdin) == NULL) break;
			color_hash[strcspn(color_hash,"\n")] = 0;
		} while (strcmp(color_hash, color_validification(color_hash, chosen_color)) != 0); 

		// Sets color for the user //
		if (strncmp(color_hash, "red", 8)==0) strncpy(color, ANSI_COLOR_RED, 8);
		if (strncmp(color_hash, "yellow", 8)==0) strncpy(color, ANSI_COLOR_YELLOW, 8);
		if (strncmp(color_hash, "green", 8)==0) strncpy(color, ANSI_COLOR_GREEN, 8);
		if (strncmp(color_hash, "blue", 8)==0) strncpy(color, ANSI_COLOR_BLUE, 8);
		if (strncmp(color_hash, "magenta", 8)==0) strncpy(color, ANSI_COLOR_MAGENTA, 8);
		if (strncmp(color_hash, "white", 8)==0) strncpy(color, ANSI_COLOR_RESET, 8);
		if (strncmp(color_hash,"cyan", 8)==0) strncpy(color, ANSI_COLOR_CYAN, 8);
	}
	return color;
}

char* color_validification(char *color, char *chosen_color) {

	// checks if color is in color list //
	char* color_list[7] = {"red","yellow","green", "blue", "magenta", "cyan", "white"};

	for (int i = 0; i < 7; i++) {
		if (strncmp(color, color_list[i], 8) == 0) {
			chosen_color = color_list[i];
		}
	} 

	return chosen_color;
}
/* Board iterations: 

- Iteration 1# 3x3
 +-------+ 
 | # # # | 
 | # # # | 
 | # # # | 
 +-------+ 

- Iteration 2# 3x3 with indicators
         +-------+       
   +---+ | # # # | +---+ 
   | X | | # # # | | O | 
   +---+ | # # # | +---+ 
         +-------+       
 
- Iteration 3# 3x3 with indicators and win counters
         +-------+       
   +-#-+ | # # # | +-#-+ 
   | X | | # # # | | O | 
   +---+ | # # # | +---+ 
         +-------+ 

*/