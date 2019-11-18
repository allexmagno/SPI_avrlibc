/* 
 * File:   UART.cpp
 * Author: root
 * 
 * Created on 16 de Setembro de 2019, 08:11
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>

FILA<uint8_t> UART::_tx_buffer(16);
FILA<uint8_t> UART::_rx_buffer(16);
bool UART::has_data = false;

UART::UART() {
}

UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb) {
    UBRR0 = F_CPU/16/baud-1;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= db | parity | sb;
}

/*UART::~UART() { 
    
}*/

void UART::put(uint8_t data){
    _tx_buffer.enfileira(data);
    UCSR0B |= (1 << UDRIE0);
};

void UART::puts(const char * msg){
    // Criar uma fila para tx_buffer
    for(int i = 0; msg[i] != 0; i++){
        put((uint8_t) msg[i]);
    }
};

uint8_t UART::get(){
    return _rx_buffer.desenfileira();
};

bool UART::get_has_data(){
    return _rx_buffer.size();
};

void UART::rx_isr_handler(){
    if(_rx_buffer.cheia()) return;
    _rx_buffer.enfileira((uint8_t) UDR0);
    
};
void UART::tx_isr_handler(){
    UDR0 = _tx_buffer.desenfileira();
    if (_tx_buffer.vazia()){
        UCSR0B &= ~(1 << UDRIE0);
    }
};

ISR(USART0_RX_vect)
{
    UART::rx_isr_handler();
}

ISR(USART0_UDRE_vect){
    UART::tx_isr_handler();
}
