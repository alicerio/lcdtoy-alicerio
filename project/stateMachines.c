#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"

// Changes the LED that is on.
void state_advance() { 

  switch(switch_state_changed){
  case 1:
    led_update();
    break;
  case 2:
    led_update();
    break;
  case 3:
    led_update();
    led_update();
    break;
  case 4:
    break;
  }
}


