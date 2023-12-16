
/**
 * This example assumes you have a means to debug over UART
 * I used an FTDI breakout board,connected RX TO TX(GPIO0 ON PICO)
 * connected TX to RX(GPIO1 on picO)
 */

#include <stdio.h>
#include "pico/stdlib.h"
#define LED     22
#define BUTTON  21

int main()
{
    stdio_init_all();
    gpio_set_function(LED, GPIO_FUNC_SIO);
    gpio_set_dir(LED, true); // set LED in as output

    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, false); // set button pin as input
    gpio_pull_down(BUTTON); // enable pull down on button pin

    uint64_t t;
    int s = 0; // states s=0 for button pushed, s=1 for button not pushed
    int i;
    int count = 0;

    while(true){

        i = gpio_get(BUTTON);
        t = time_us_64() + 100; // get current timestamp

        switch(s){
            case 0: // button not pressed
                if(i){ // confirm the button was pushed
                    s = 1;
                    count++;
                    printf("Button push %d \n\r", count);
                }
                break;

            case 1: // button pressed
                if(!i){
                    s = 0;

                }
                break;

            default:
                s = 0;
        }

        sleep_until((absolute_time_t){t}); // convert t to absolute_time_t

    }

}
