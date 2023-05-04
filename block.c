/** @file   game_mechanics.h
    @author James Claridge, Vedang Gaikwad
    @date   20 Oct 2021
    @brief  Source file responsible for moving the block across the screen
*/

#include "system.h"
#include "block.h"

/** Array used for quickly calculating 2 to the power of something*/
uint8_t power2[] = {0, 1, 2, 4, 8, 16, 32, 64};

/** Changes the position of the block.
    @param block_position The current position of the moving block
    @param array the bitmap of the moving block */
void block_position_mover(block_position_t* block_position, uint8_t array[])
{
    uint8_t prev_x = block_position->x_position;
    static bool left = 0;
    size_t limit = 0;
    if (prev_x + block_position->size<= 5) {
        limit = prev_x + block_position->size;
    } else {
        limit = 5;
    }
    for (size_t counter = 0; counter < 5; counter++) {
        *(array + counter) = 0;
    }
    for (size_t counter = prev_x; counter < limit; counter++) {
        *(array + counter) = power2[7 - block_position->y_position];
    }
    if (block_position->x_position + block_position->size == 5) {
        left = 1;
    } else if (block_position->x_position == 0) {
        left = 0;
    }
    if (left) {
        block_position->x_position -= 1;
    } else {
        block_position->x_position += 1;
    }
}
