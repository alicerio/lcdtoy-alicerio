#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

int main() {
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  int j;
  clearScreen(COLOR_BLUE);


  for(j = 0; j < 15; j++) {
    drawPixel(0,j,COLOR_BLUE);
    drawPixel(j,j,COLOR_BLUE);
    drawPixel(j,15,COLOR_BLUE);
  }
 
