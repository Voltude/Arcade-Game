/** @file   game.c
    @author James Claridge, Vedang Gaikwad
    @date   20 Oct 2021
    @brief  Main C file for the brick stacker game, involving the main game logic loop
*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include <stdbool.h>
#include "timer.h"
#include <stdio.h>
#include "ledmat.h"
#include "navswitch.h"
#include "block.h"
#include "game_display.h"
#include "game_mechanics.h"

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/** Plays game using modules.
    @return an int as main usually does.  */
int main (void)
{
    system_init ();
    ledmat_init();
    navswitch_init();

    uint8_t count = 0;
    uint8_t moving_block_bitmap[] = {64, 64, 64, 0, 0};
    uint8_t tower[] = {0, 0, 0, 0, 0};
    block_position_t block_position = {0, 0, 3};
    uint8_t speed = 255;
    uint8_t count2 = 0;
    uint8_t speed2 = 1;
    uint8_t score;
    bool game_over_bool = 0;

    TCCR0B = 0x02;
    TCNT0 = 0;

    while (1) {
        if (!game_over_bool){
            if (TCNT0 == 2 && !game_over_bool) {
                if (count >= speed) {
                    block_position_mover(&block_position, moving_block_bitmap);
                    count = 0;
                } else {
                    count++;
                }
            }
            if (TCNT0 == 124) {
                if (count2 == speed2) {
                    navswitch_update();
                    display(moving_block_bitmap, tower);
                    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                        game_over_bool = game_over(moving_block_bitmap, tower, &block_position);
                        if (!game_over_bool) {
                            speed -= 4;
                            }
                        }
                } else {
                    count2++;
                }
            }
        } else {
            score = get_score();
            score_init(score);
            display_score();
        }
    }
}
