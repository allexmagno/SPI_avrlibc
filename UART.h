/* 
 * File:   UART.h
 * Author: root
 *
 * Created on 16 de Setembro de 2019, 08:11
 */
// static = atributo global da classe

#ifndef UART_H
#define	UART_H
#include "FILA.h"
#include <stdint.h>

class UART {
public:
    
    enum DATABITS_t {
        DATABITS_5 = 0,
        DATABITS_6 = 1,
        DATABITS_7 = 2,
        DATABITS_8 = 3
    };

    
    enum PARITY_t {
        NONE = 0,
        EVEN = 32,
        ODD = 48  
    };
    
    enum STOPBITS_t {
        STOPBIT_1 = 16,
        STOPBIT = 0
    };
    
    UART();
    UART(uint32_t baud = 19200, DATABITS_t db=DATABITS_8, PARITY_t parity = NONE, STOPBITS_t sb = STOPBIT_1);
   // virtual ~UART();
    
    void put(uint8_t data);
    void puts(const char * msg);
    uint8_t get();
    bool get_has_data();
    static void rx_isr_handler();
    static void tx_isr_handler();
    
private:
    
    static bool has_data;
    static FILA<uint8_t> _rx_buffer;
    static FILA<uint8_t> _tx_buffer;

};

#endif	/* UART_H */