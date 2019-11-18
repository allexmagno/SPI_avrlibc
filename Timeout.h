/* 
 * File:   Timeout.h
 * Author: root
 *
 * Created on 25 de Setembro de 2019, 07:54
 */

#ifndef TIMEOUT_H
#define	TIMEOUT_H
#include <stdint.h>

typedef void (*CALLBACK_t)(void);

class Timeout {
public:
    Timeout();
//    virtual ~Timeout();
    void config(uint32_t interval, CALLBACK_t callback);
    void checkTimeout();
    void callback();
    void incCounter();
    bool enable();
    bool event();
private:
    bool _event;
    bool _enable;
    CALLBACK_t _callback;
    uint32_t _counter;
    uint32_t _interval;
};

#endif	/* TIMEOUT_H */

