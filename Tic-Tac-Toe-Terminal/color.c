#include "tic.h"

void change_character_color(Board *game_sourse, Player *p1, Player *p2) {
    printf("\033[17;5H");
	printf("choose which player \n       (%c or %c) : ", *p1->character, *p2->character);
	char side = safe_input(game_sourse, p1, p2, 'I', 2, *p1->character, *p2->character);
	// determine the player //
	if (side == *p1->character || side == *p2->character) {
        change_color(game_sourse, p1, p2, side, "Characters");
	}
}

void change_color(Board *game_sourse, Player *p1, Player *p2, char target, char *label) {
    
    char color_hash[COLOR_COMPLEXITY];
    char chosen_color[COLOR_COMPLEXITY];

    if (target != *game_sourse->space && target != '\0')
	    *game_sourse->target = target;

	// Collects color form the user //
	do {
        // Checks if the target is the boarder or a character 
        if (target == '\0') printf("\n input the color you want for the %s \n color :", label);
        if (target != '\0') printf("\n input the color you want for %c \n color : ", target);

		if(fgets(color_hash, sizeof(color_hash), stdin) == NULL) break;
		color_hash[strcspn(color_hash,"\n")] = 0; // removes the new line character

	} while (strcmp(color_hash, color_validification(game_sourse ,color_hash, chosen_color)) != 0); 
    if (*game_sourse->target == *p1->character && target != *game_sourse->space) strncpy(p1->color, color_input(game_sourse, color_hash), COLOR_COMPLEXITY); 
    if (*game_sourse->target == *p2->character && target != *game_sourse->space) strncpy(p2->color, color_input(game_sourse, color_hash), COLOR_COMPLEXITY);
    if (target == *game_sourse->space) strncpy(game_sourse->space_color, color_input(game_sourse, color_hash), COLOR_COMPLEXITY);
    if (target == '\0' && (strncmp(label, "Game boarder", 20) == 0)) strncpy(game_sourse->boarder_color, color_input(game_sourse, color_hash), COLOR_COMPLEXITY);
    if (target == '\0' && (strncmp(label, "Turn boarder", 20) == 0)) strncpy(game_sourse->turn_color, color_input(game_sourse, color_hash), COLOR_COMPLEXITY);
    if (target == '\0' && (strncmp(label, "Pending boarder", 20) == 0)) strncpy(game_sourse->pending_color, color_input(game_sourse, color_hash), COLOR_COMPLEXITY);

    print_to_terminal(game_sourse, p1, p2);
    printf("\033[%d;%dH", BOARD_YOFFSET + (*game_sourse->y_pos), BOARD_XOFFSET + ((*game_sourse->x_pos)*2));
}

char* color_input(Board *game_sourse, char *color) {
    // Looks for a match then send its back //
	for (int i = 0; i < COLOR_AMOUNT; i++) {
		if (strncmp(color, game_sourse->ANSI->color_list[i], COLOR_COMPLEXITY) == 0) {
            return color_parse(game_sourse, i);
		}
	} 
	return ANSI_COLOR_RESET;
}

char* color_validification(Board *game_sourse, char *color, char *chosen_color) {
	for (int i = 0; i < COLOR_AMOUNT; i++) {
		if (strncmp(color, game_sourse->ANSI->color_list[i], COLOR_COMPLEXITY) == 0) {
			chosen_color = game_sourse->ANSI->color_list[i];
		}
	} 
	return chosen_color;
}

void change_color_types(Board *game_sourse, Player *p1, Player *p2) {
    printf("What type of color would you like \n (N)Normal, (B)Bright, (G)Background, (Y)Background+Bright \n Input:");
    char input = safe_input(game_sourse, p1, p2, 'I', 4, 'N', 'B', 'G', 'Y');
    if (input == 'N') *game_sourse->color_type = 'A';
    if (input == 'B') *game_sourse->color_type = 'B';
    if (input == 'G') *game_sourse->color_type = 'C';
    if (input == 'Y') *game_sourse->color_type = 'D';
    printf("\nChange all elements to that set (Y)yes (N)no : ");
    input = safe_input(game_sourse, p1, p2, 'I', 2, 'N', 'Y');
    if (input == 'Y') {
        change_all_color(game_sourse, p1, p2);
    }
}

void change_all_color(Board *game_sourse, Player *p1, Player *p2) {
    strncpy(p1->color, aspect_change(game_sourse, p1->color), COLOR_COMPLEXITY); 
    strncpy(p2->color, aspect_change(game_sourse, p2->color), COLOR_COMPLEXITY);
    strncpy(game_sourse->space_color, aspect_change(game_sourse, game_sourse->space_color), COLOR_COMPLEXITY);
    strncpy(game_sourse->boarder_color, aspect_change(game_sourse, game_sourse->boarder_color), COLOR_COMPLEXITY);
    strncpy(game_sourse->turn_color, aspect_change(game_sourse, game_sourse->turn_color), COLOR_COMPLEXITY);
    strncpy(game_sourse->pending_color, aspect_change(game_sourse, game_sourse->pending_color), COLOR_COMPLEXITY);
}

char* aspect_change(Board *game_sourse, char* target) {
    int index;
    for (int i = 0; i < COLOR_AMOUNT; i++) {
        if (strncmp(target, game_sourse->ANSI->normal[i], COLOR_COMPLEXITY) == 0) index = i;
        if (strncmp(target, game_sourse->ANSI->bright[i], COLOR_COMPLEXITY) == 0) index = i;
        if (strncmp(target, game_sourse->ANSI->background[i], COLOR_COMPLEXITY) == 0) index = i;
        if (strncmp(target, game_sourse->ANSI->bright_background[i], COLOR_COMPLEXITY) == 0) index = i;     
    }
    return color_parse(game_sourse, index);
}

char* color_parse(Board *game_sourse, int index) {
    if (*game_sourse->color_type == 'A') return game_sourse->ANSI->normal[index];
    if (*game_sourse->color_type == 'B') return game_sourse->ANSI->bright[index];
    if (*game_sourse->color_type == 'C') return game_sourse->ANSI->background[index];
    if (*game_sourse->color_type == 'D') return game_sourse->ANSI->bright_background[index];
    return game_sourse->ANSI->normal[index]; // normal is the default
}