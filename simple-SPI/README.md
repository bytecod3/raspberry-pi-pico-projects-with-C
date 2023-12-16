##### Set up

To set up a full SPI interface, you need to set a line for each of the SPI lines

1. one for MOSI
2. one for MISO 
3. one for SCLK
4. the CS pin can be used from any GPIO, its not part of the standard SPI implementation

##### Code

You must add the following directive at the top of the ```main.c``` file:

```c
#include "hardware/spi.h"
```

Then, in the CMakeLists.txt inside the main folder, have the ```target_link_libraries``` line look like this:

```c
target_link_libraries(main pico_stdlib hardware_spi) 
```

##### SPI functions 

These can be split into 3:

1. Initialization functions
2. Config functions
3. Data transfer functions

### 1. Initialization functions 

```c
spi_init(spi, baudrate); // spi is a pointer to SPI instance, baudrate is the click speed, anywhere between 125MHz and 3.8KHz
spi_deinit(spi); // destroy an spi connection
```

### 2. Config functions 

To set baudrate:

```c 
spi_set_baudrate(spi, baudrate);
```

To select whether Pico will be a slave or master:

```c 
spi_set_slave(spi, slave);
```

Most important function, setting the format:

```c
spi_set_format(spi,
              databits,
              cpol,
              cpha,
              order); // sets the SPI mode, see the screenshot below
```

It is to be noted that the PICO is SPI_MSB first, therefore we set the mode as follows: 

```c 
SPI_CPHA_O or SPI_CPHA_1 together with
SPI_CPOL_0 or SPI_CPOL_1 
```

### 3. Data  transfer functions

To read 16 bit data, use:

```c
spi_read16_blocking(spi, src, dst, len); // src and dst are arrays of the same length
```

To write 16 bit data, use:

```c
spi_write16_blocking(spi, src, len); // src is an array of 16-bit elements
```

Note that these functions are blocking, therefore they return only when the data transfer is complete.

You can read and write at the same time with:

```c
spi_write16_read16_blocking(spi, src, dst, len)
```

Example code:

```c
// this sends 3 elements in wBuff and receives back 3 elements in rBuff

int len = 3;
uint16_t wBuff = {'A', 'B', 'C'};
uint16_t rBuff[len];


int n = spi_write16_read16_blocking(spi0, wBuff, rBuff, len);

```

We can chose to transfer multiple bytes at once or single bytes individually using multiple transfer calls. 

The best approach is to use the buffer transfers. In which case, the CS line can be left active for the entire transfer i.e it is not necessary to deactivate it between each byte. 

```NB```

The nature of the transfer is that the first element is sent at the same time that the first element is received. i.e unlike other protocols, the whole send buffer is not sent before the received data comes back. 

The entire data transfer works a data element at a time - the first element is sent while the first element is being received, then the second element is sent at the same time as the second is being received and so on.

