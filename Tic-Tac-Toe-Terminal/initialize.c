#include "tic.h"

Colors* initialize_colors() {

    // List of all color inputs //
    char* color_list[COLOR_AMOUNT] = 
    { 
        "red", 
        "yellow", 
        "green", 
        "blue", 
        "magenta", 
        "cyan", 
        "white" 
    };

    // List of all Normal colors //
    char* normal_colors[COLOR_AMOUNT] = 
    { 
        ANSI_COLOR_RED, 
        ANSI_COLOR_YELLOW, 
        ANSI_COLOR_GREEN, 
        ANSI_COLOR_BLUE, 
        ANSI_COLOR_MAGENTA, 
        ANSI_COLOR_CYAN, 
        ANSI_COLOR_WHITE 
    };

    // List of all Bright colors //
    char* bright_colors[COLOR_AMOUNT] = 
    { 
        ANSI_COLOR_RED_BRIGHT, 
        ANSI_COLOR_YELLOW_BRIGHT, 
        ANSI_COLOR_GREEN_BRIGHT, 
        ANSI_COLOR_BLUE_BRIGHT, 
        ANSI_COLOR_MAGENTA_BRIGHT, 
        ANSI_COLOR_CYAN_BRIGHT, 
        ANSI_COLOR_WHITE_BRIGHT 
    };

    // List of all Background colors //
    char* backgorund_colors[COLOR_AMOUNT] = 
    { 
        ANSI_COLOR_RED_BG, 
        ANSI_COLOR_YELLOW_BG, 
        ANSI_COLOR_GREEN_BG, 
        ANSI_COLOR_BLUE_BG, 
        ANSI_COLOR_MAGENTA_BG, 
        ANSI_COLOR_CYAN_BG, 
        ANSI_COLOR_WHITE_BG 
    };

    // List of all Bright Background colors //
    char* bright_background_colors[COLOR_AMOUNT] = 
    { 
        ANSI_COLOR_RED_BRIGHT_BG, 
        ANSI_COLOR_YELLOW_BRIGHT_BG, 
        ANSI_COLOR_GREEN_BRIGHT_BG, 
        ANSI_COLOR_BLUE_BRIGHT_BG, 
        ANSI_COLOR_MAGENTA_BRIGHT_BG, 
        ANSI_COLOR_CYAN_BRIGHT_BG, 
        ANSI_COLOR_WHITE_BRIGHT_BG 
    };

    // Allocation of memory //
    Colors *ANSI = malloc(sizeof(Colors));
    if (ANSI == NULL) exit(1);

    // Filling the struct //
    for (int i = 0; i < COLOR_AMOUNT; i++) {
        strncpy(ANSI->color_list[i], color_list[i], COLOR_COMPLEXITY);
        strncpy(ANSI->normal[i], normal_colors[i], COLOR_COMPLEXITY);
        strncpy(ANSI->bright[i], bright_colors[i], COLOR_COMPLEXITY);
        strncpy(ANSI->background[i], backgorund_colors[i], COLOR_COMPLEXITY);
        strncpy(ANSI->bright_background[i], bright_background_colors[i], COLOR_COMPLEXITY);        
    }
    return ANSI;
}