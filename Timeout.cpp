/* 
 * File:   Timeout.cpp
 * Author: root
 * 
 * Created on 25 de Setembro de 2019, 07:54
 */

#include "Timeout.h"

Timeout::Timeout(){
    this->_event = false;
    this->_enable = false;
    this->_interval = 0;
    this->_counter = 0; 
}

//Timeout::~Timeout() {}

void Timeout::config(uint32_t interval, CALLBACK_t callback){
    this->_callback = callback;
    this->_interval = interval;
    this->_enable = true;
}

void Timeout::checkTimeout(){
    if (this->_enable){
       incCounter();
    }
}

void Timeout::callback(){
    (*_callback)();
    this->_event = false;
}

void Timeout::incCounter(){
    ++this->_counter;
    if(this->_counter == this->_interval){
        this->_event = true;
        this->_counter = 0;
    }
}

bool Timeout::event()
{
	return this->_event;
}

bool Timeout::enable()
{
	return this->_enable;
}