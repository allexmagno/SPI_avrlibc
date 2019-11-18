

#ifndef GPIO_H
#define	GPIO_H

#include "GPIO_Port.h"

class GPIO {
public:
    enum PortDirection_t {
        INPUT = 0,
        OUTPUT = 1
    };
    
    GPIO(uint8_t id, PortDirection_t dir);
    //~GPIO();
    GPIO();
    bool get();
    void set(bool val = 1);
    void clear();
    void toggle();

private:
    GPIO_PORT::GPIO_Port * _port; 
    
    uint8_t _bit;
};



#endif	/* GPIO_H */