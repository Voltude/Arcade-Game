/** @file   game_mechanics.h
    @author James Claridge, Vedang Gaikwad
    @date   20 Oct 2021
    @brief  Header file for the module containing the back end logic for the game such as checking if the game is over and
    calculating the score
*/

#ifndef GAME_MECHANICS_H
#define GAME_MECHANICS_H

#include "system.h"
#include "block.h"
#include <stdbool.h>

/** Returns true if the game has ended, either by the player runing out of space or missing the tower*/
bool game_over(uint8_t* block, uint8_t* tower, block_position_t* block_position);

/**Returns the score of the game*/
uint8_t get_score(void);

#endif /* GAME_MECHANICS_H */
