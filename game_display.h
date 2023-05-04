/** @file   game_mechanics.h
    @author James Claridge, Vedang Gaikwad
    @date   20 Oct 2021
    @brief  Header file for the module containing logic responsible for displaying the game and the score
*/

#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15

/**Function responsible for setting up the display to display the score but no actually displaying it*/
void score_init(uint8_t number);

/**Function responsible for displaying the score of the game*/
void display_score(void);

/**Function responsible for displaying the actual game*/
void display(uint8_t* tower, uint8_t* block);

#endif /* GAME_DISPLAY_H */
