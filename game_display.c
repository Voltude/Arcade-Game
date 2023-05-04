/** @file   game_mechanics.h
    @author James Claridge, Vedang Gaikwad
    @date   20 Oct 2021
    @brief  Source file for the module containing logic responsible for displaying the game and the score
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "game_display.h"
#include <stdio.h>
#include <string.h>
#include "ledmat.h"

/** Initializes the modules and tinygl needed to display a scrolling score.
    @param number The score to display
*/
void score_init(uint8_t number)
{
    tinygl_init(PACER_RATE);
    pacer_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    char score[4];
    sprintf(score, "%d", number);
    tinygl_text(strcat("SCORE :", score));
}

/** Displays the game in it's 2 parts of the moving block and the tower.
    @param block The current bit map of the moving block
    @param tower The bit map of the tower */
void display(uint8_t* tower, uint8_t* block)
{
    for (size_t counter = 0; counter < 5; counter ++) {
        ledmat_display_column(*(tower + counter) | *(block + counter), counter);
    }
}

/** Displys the score using tinygl*/
void display_score(void)
{
    while (1) {
        pacer_wait ();
        tinygl_update ();
    }

}
