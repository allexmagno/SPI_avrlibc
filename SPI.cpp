#include "SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>

bool SPI::has_data = false;
GPIO SPI::_slave = GPIO();

SPI::SPI(Mode_t md, ClockRate_t sck, DataMode_t dtm, DataOrder_t dto, GPIO *slaves) {
    _msk = (sck % 4);
    if (md){
        if (sck > 4){
            SPCR = _msk;
            SPSR = 1;
        }else{
            SPCR = _msk;
        }
        SPCR |= (1 << MSTR);
        DDRB |= (1 << PB2) | (1 << PB1); // Configura MOSI e SCK
        
    }else{
        DDRB = (1<<PB3);
    }
    SPCR |= (1<<SPE);
    _slaves = slaves;
};

void SPI::put(uint8_t data){
    SPDR = data; // Envia dado para o registrador
    SPCR |= (1 << SPIE);
    
};

void SPI::puts(const char * msg){
    for(int i = 0; msg[i] != 0; i++){
        put((uint8_t) msg[i]);
    }
};


uint8_t SPI::get(){
    //  Wait for reception complete
    while(!(SPSR & (1<<SPIF)));
    // Return Data Register 
    return SPDR;
}


void SPI::handler(){
    _slave.toggle();
    has_data = true;
    
};

void SPI::select_slave(uint8_t index){
    _slave = _slaves[index];
    _slave.toggle();
};

bool SPI::get_has_data(){
    return has_data;
}


ISR(SPI_STC_vect){
    SPI::handler();
}

/*
void SPI::rx_isr_handler(){
    if(_rx_buffer.cheia()) return;
    _rx_buffer.enfileira((uint8_t) UDR0);
    
};

void SPI::tx_isr_handler(){
    put(_tx_buffer.desenfileira());
    if (_tx_buffer.vazia()){
        UCSR0B &= ~(1 << UDRIE0);
    }
};*/
