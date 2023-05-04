/** @file   game_mechanics.c
    @author James Claridge, Vedang Gaikwad
    @date   20 Oct 2021
    @brief  The c file for the module responsible for checking if the game is over and getting the score
*/

#include "system.h"
#include "block.h"
#include "game_mechanics.h"
#include <stdbool.h>

/** Array used for keeping track of the cumltive powers of 2 in reverse*/
uint8_t power2_cumlative[] = {127, 126, 124, 120, 112, 96, 64};

/**Int used to represent the game score*/
static uint8_t score = 0;

/** Checks if game is over, while also keeping track of the score.
    @param block The current bit map of the moving block
    @param tower The bit map of the tower
    @param block_position The structure containing information referencing the x and y postiions of the block as well as it's size
    @return a bool, true if the game is over, false if not  */
bool game_over(uint8_t* block, uint8_t* tower, block_position_t* block_position)
{
    for (size_t counter = 0; counter < 5; counter++) {
        if (block_position->size != 0) {
            if ((*(tower + counter) + *(block + counter) == 0) || (*(tower + counter) + *(block + counter) == power2_cumlative[6 - block_position->y_position])
        || (*(tower + counter) != 0 && *(block + counter) == 0)) {
                *(tower + counter) |= *(block + counter);
                score += 1;
            } else {
                block_position->size -=1;
                *(block + counter) = 0;
            }
        }
    }
    if (block_position->size != 0) {
        block_position->y_position += 1;
        block_position->x_position = 0;
    }
    return block_position->size == 0 || block_position->y_position == 7;
}

/** Returns the score of the game.
    @return an integer which is the score of the game  */
uint8_t get_score(void)
{
    return score;
}
