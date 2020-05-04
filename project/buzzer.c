#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "stateMachines.h"

static int counterSong1 = 0;
static int counterSong2 = 0;

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void star_mario() {
  switch (counterSong1) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 6:
  case 8: buzzer_set_period(950); counterSong1++; break;
  case 5:
  case 7: buzzer_set_period(1130); counterSong1++; break;
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 15:
  case 17: buzzer_set_period(1000);
    if(counterSong1 == 17) {
      counterSong1 = 0;
    }
    else {
      counterSong1++;
    }
    break;
  case 14:
  case 16: buzzer_set_period(1270); counterSong1++; break;
  }
}

void song() {
  switch (counterSong2) {
  case 0:
  case 1:
  case 2:
  case 4: buzzer_set_period(400); counterSong2++; break;
  case 3: buzzer_set_period(670); counterSong2++; break;
  case 5: buzzer_set_period(934); counterSong2++; break;
  case 6: buzzer_set_period(1000); counterSong2 = 0; break;
  }
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}


    
    
  

