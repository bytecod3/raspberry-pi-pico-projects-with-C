/**
Take input from a tactile switch and toggle an LED
No debounce
**/


#include "pico/stdlib.h"
#define BUTTON 21
#define LED 22

int main(){
    gpio_init(22); // sets line to input by default
    gpio_set_dir(22, true); // set pin 22 to output
    
    int state;
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, false); // set button pin as input
    gpio_pull_up(BUTTON);
    
    uint32_t value;
    

    while(true){
        state = gpio_get(BUTTON); // read the input line
        
        if(!state){
            gpio_put(LED, 1);
        } else {
            gpio_put(LED, 0);
        }
        
    }


}
