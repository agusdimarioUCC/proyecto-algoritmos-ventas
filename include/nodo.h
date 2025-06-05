#ifndef NODO_H
#define NODO_H

#include <utility>   // std::move

template <class T>
class Nodo
{
public:
    // ctor: el segundo parámetro default = nullptr
    explicit Nodo(const T& d, Nodo* s = nullptr) noexcept
        : dato(d), siguiente(s)
    {
    }

    explicit Nodo(T&& d, Nodo* s = nullptr) noexcept
        : dato(std::move(d)), siguiente(s)
    {
    }

    // getters (const-correctos)
    const T& getDato() const noexcept { return dato; }
    T& getDato() noexcept { return dato; }

    Nodo* getSiguiente() noexcept { return siguiente; }
    const Nodo* getSiguiente() const noexcept { return siguiente; }

    // setters
    void setDato(const T& d) noexcept { dato = d; }
    void setDato(T&& d) noexcept { dato = std::move(d); }

    void setSiguiente(Nodo* s) noexcept { siguiente = s; }

private:
    T dato;
    Nodo* siguiente;
};

#endif  // NODO_H
