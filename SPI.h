/* 
 * File:   SPI.h
 * Author: magno
 *
 * Created on 21 de Outubro de 2019, 07:41
 */

#ifndef SPI_H
#define	SPI_H
#include <stdint.h>
#include "GPIO.h"
#include "FILA.h"

class SPI {
public:
    
    enum Mode_t{
        MASTER = 1,
        SLAVE = 0
    };
    //mod4
    enum ClockRate_t{ 
        X_2 = 4,
        X_4 = 0,
        X_8 = 5,
        X_16 = 1,
        X_32 = 6,
        X_64 = 2,
        X_128 = 7
    };
    
    enum DataMode_t{
        MODE_0 = 0,
        MODE_1 = 4,
        MODE_2 = 8,
        MODE_3 = 12
    };
    
    enum DataOrder_t{
        LSB = 32,
        MSB = 0
    };
    
    SPI();
    SPI(Mode_t md = MASTER, ClockRate_t sck = X_4, DataMode_t dtm = MODE_0, DataOrder_t dto = MSB, GPIO slaves[] = 0);
    void put(uint8_t data);
    void puts(const char * msg);
    uint8_t get();
    bool get_has_data();
    void select_slave(uint8_t index);
    static void handler();

private:
    static bool has_data;
    uint8_t _msk;
    GPIO *_slaves;
    static GPIO _slave;
    static FILA<uint8_t> _rx_buffer;
    static FILA<uint8_t> _tx_buffer;
};

#endif	/* SPI_H */