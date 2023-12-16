/**
 * SPI LOOPBACK
demonstrate SPI without any ecternal components
**/


#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>

int main(){
    spi_init(spi0, 500 * 1000); // using 500kHz

    // set the lines we are using to SPI mode
    gpio_set_function(4, GPIO_FUNC_SPI);
    gpio_set_function(6, GPIO_FUNC_SPI);
    gpio_set_function(7, GPIO_FUNC_SPI);

    // configure the SPI interface
    // we are using 8-bit and SPI mode 0
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);


    // we can now send data and receive it back
    // 0xAA generated alternating wave shape easy to recognize on
    // a scope/logic analyzer
    //uint8_t read_data = bcm2835_spi_transfer(0xAA);

    // check that the received data matches the send data
    uint16_t wBuff[1] = {0xAA};
    uint16_t rBuff[1];

    int n = spi_write16_read16_blocking(spi0, wBuff, rBuff, 1);

    // close the bus
    spi_deinit(spi0);

    printf("%X %X %d", wBuff[0], rBuff[0], n);

    while(true){

    }

}
