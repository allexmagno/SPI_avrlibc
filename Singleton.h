/* 
 * File:   Singleton.h
 * Author: root
 *
 * Created on 25 de Setembro de 2019, 07:45
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

template<typename T>
class Singleton {
public:
    Singleton() { _singleton = static_cast<T*>(this); }
    ~Singleton() { _singleton = 0; }

    static T * self() { return _singleton; }

private:
    static T * _singleton;
};

template<typename T>
T * Singleton<T>::_singleton;

#endif /* SINGLETON_H_ */

