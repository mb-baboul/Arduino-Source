/*  Pokemon BDSP Arduino Programs
 * 
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 * 
 */

#include "Programs/EggHatcher.h"


const uint8_t   BOXES_TO_HATCH  =   3;
const uint16_t  STEPS_TO_HATCH  =   5120;   //  Lookup the # of steps on Serebii.

//  After hatching a box, save the game and reset. This will recover from game crashes.
const bool SAVE_AND_RESET       =   true;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Advanced Settings (you shouldn't need to change these)

//  Additional time added to the spinning. If any shinies are hatched, they will
//  eat into this safety buffer along with any other unexpected slowdowns.
//  Hatching a shiny takes 2 seconds longer than a non-shiny.
//
//  If you see that the program is going into Y-COMM or there is less than 5
//  seconds of extra spinning after the last egg in the batch, please report
//  this as a bug. As a temporary work-around, you can increase this number.
const uint16_t SAFETY_TIME  =   10 * TICKS_PER_SECOND;

//  Total animation time for hatching 5 eggs when there are no shinies.
const uint16_t HATCH_DELAY  =   105 * TICKS_PER_SECOND;



