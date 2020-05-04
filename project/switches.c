#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "lcddraw.h"
#include "lcdutils.h"

char switch_state_down, switch_state_changed, tempo,s1,s2,s3,s4; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p1val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
  s1 = (p1val & SW1) ? 1 : 0; //switch 1

  s2 = (p1val & SW2) ? 1 : 0; //switch 2

  s3 = (p1val & SW3) ? 1 : 0; //switch 3

  s4 = (p1val & SW4) ? 1 : 0; //switch 4
  
    buzzer_set_period(0);
  
  if (!(p1val & s1)) {
    state_advance();
    tempo = 12;
    star_mario(); // Calls star song from buzzer.
    clearScreen(COLOR_PINK); // Background color.
    drawString5x7(5,50, "Alan Licerio's", COLOR_NAVY, COLOR_CHOCOLATE);
    drawString5x7(5,70, "project 3.", COLOR_NAVY, COLOR_CHOCOLATE);
    switch_state_changed = 1; // Mantains state.
  }

  else if (!(s2 & p1val)) {
    state_advance();
    clearScreen(COLOR_GOLD);
    drawString5x7(5,50, "   CHOICE 2:V   ", COLOR_RED, COLOR_YELLOW);
    buzzer_set_period(400); // Sets buzzer frequency.
    switch_state_changed = 2;
    led_update(); // Led is on.
  }

  else if (!(s3 & p1val)) {
    clearScreen(COLOR_TURQUOISE);
    drawString5x7(5,50, "   CHOICE 3:)   ", COLOR_WHITE, COLOR_HOT_PINK);
    song(); // Calls song method from buzzer.
    tempo = 50;
    switch_state_changed = 3;
    led_update();
  }

  else if (!(s4 & p1val)) {
    clearScreen(COLOR_RED);
    drawString5x7(5,50, "   CHOICE 4: )   ", COLOR_WHITE, COLOR_HOT_PINK);
    buzzer_set_period(800);
    switch_state_changed = 4;
    led_update();
  }
  
  //next_state();
  switch_state_changed = 1;
  led_update();
}
