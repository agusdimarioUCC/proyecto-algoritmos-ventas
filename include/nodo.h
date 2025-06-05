#ifndef NODO_H
#define NODO_H

#include <memory>

template <class T>
class Nodo {
public:
    explicit Nodo(const T& d, Nodo* s = nullptr) noexcept
        : dato(d), siguiente(s) {}

    // getters “const”, no copian el dato innecesariamente
    const T& getDato()   const noexcept { return dato; }
    Nodo*    getSig()    const noexcept { return siguiente; }

    // setters
    void setDato(const T& d)   noexcept { dato = d; }
    void setSig(Nodo* s)       noexcept { siguiente = s; }

private:
    T     dato;
    Nodo* siguiente;
};

#endif  // NODO_H
