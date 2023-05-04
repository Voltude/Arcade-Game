/** @file   block.h
    @author James Claridge, Vedang Gaikwad
    @date   20 Oct 2021
    @brief  Header file for the module containing logic responsible for the moving block in a game
*/

#ifndef BLOCK_H
#define BLOCK_H

#include "system.h"
#include <stdio.h>

/** The structure responsible for keeping track of where the block is on the screen*/
typedef struct {
    uint8_t x_position;
    uint8_t y_position;
    size_t size;
} block_position_t;

/** Function responsible for moving the block back and forth on the screen*/
void block_position_mover(block_position_t* block, uint8_t array[]);

#endif /* BLOCK_H */
