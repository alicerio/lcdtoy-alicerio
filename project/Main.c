#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"


void main() {
  configureClocks();
  switch_init();
  buzzer_init();
  led_init();
  enableWDTInterrupts();
  
  lcd_init();

  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE); // Background color.
  // Display Strings
  drawString5x7(05,30, "Hello, choose one", COLOR_GREEN, COLOR_RED);
  drawString5x7(05,55, "option.",COLOR_GREEN,COLOR_RED);
  drawString5x7(10,75, " Choice 1", COLOR_WHITE, COLOR_BLUE);
  drawString5x7(10,85, " Choice 2 ", COLOR_WHITE, COLOR_BLUE);
  drawString5x7(10,95, " Choice 3", COLOR_WHITE, COLOR_BLUE);
  drawString5x7(10,105, " Choice 4", COLOR_WHITE, COLOR_BLUE);

  or_sr(0x18);
}
