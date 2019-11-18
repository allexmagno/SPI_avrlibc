/* 
 * File:   FILA.h
 * Author: root
 *
 * Created on 21 de Setembro de 2019, 14:27
 */

#ifndef FILA_H
#define	FILA_H
#include <stdlib.h>

template <typename T> class FILA {
public:
    FILA(unsigned int N):cap(N) {
        inicio = 0;
        fim = 0;
        itens = 0;
        buffer = (T*) malloc(cap*sizeof(T));
    }

    FILA(const FILA& outra) {
        itens = outra.itens;
        cap = outra.cap;
        inicio = outra.inicio;
        buffer = new T[cap];

        for(int j = 0; j < cap; j++){
           int pos = (outra.inicio + j) % outra.cap;
           buffer[j] = outra.buffer[pos];
        }
        fim = outra.fim;
      }

    FILA<T>& operator=(const FILA& outra) {
        itens = outra.itens;
        if(cap < outra.cap) cap = outra.cap;
        inicio = 0;
        fim = cap;
        delete[] buffer;
        buffer = new T[cap];

        for(int j = 0; j < cap; j++){
           int pos = (outra.inicio + j) % outra.cap;
           buffer[j] = outra.buffer[pos];
        }
        return *this;
      }

    void enfileira(const T& algo){
        if(!cheia()) {// throw "Fila cheia!";

        buffer[fim] = algo;
        fim = (fim + 1) % cap;
        itens++;
        }
    }


    T desenfileira() {
        if (itens == 0){ //throw "Fila vazia";
            return 0;
        }
        if(cap > 0){
            int pos = inicio;
            if(inicio == cap-1) {
                inicio = 0;
            }
            else{
                inicio++;
            } 
            itens--;
            return buffer[pos];
        }
    }

    T desenfileiraFim() {
        if (itens == 0) throw "Fila vazia";
        if(cap > 0){
        if(fim == 0)fim = cap-1;
        else fim--;
        itens--;

      return buffer[fim]; 
        }
    }
    
    const T& frente() const {
        if(vazia()) throw "Fila Vazia!";
        return buffer[inicio];
    }

    bool vazia() const {
        return itens == 0;
    }

    bool cheia() const {
       return itens == cap;
    }

    unsigned int capacidade() const {
        return cap;
    }

    unsigned int size() const {
        return itens;
    }
    
    void esvazia(){
        itens = 0;
    }

    private:
    unsigned int cap, itens;
    T * buffer;
    unsigned int inicio, fim, marc;
};

#endif	/* FILA_H */
