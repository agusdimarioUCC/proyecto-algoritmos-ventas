#ifndef LISTA_H
#define LISTA_H

#include <cassert>
#include <iostream>
#include "Nodo.h"

template <class T>
class Lista {
   public:
    Lista()  noexcept : inicio(nullptr), tam(0) {}
    // -- Regla de los cinco
    ~Lista()                { vaciar(); }
    Lista(const Lista& o)   { copiarDe(o); }
    Lista& operator=(const Lista& o) {
        if (this != &o) { vaciar(); copiarDe(o); }
        return *this;
    }
    Lista(Lista&& o) noexcept : inicio(o.inicio), tam(o.tam) {
        o.inicio = nullptr; o.tam = 0;
    }
    Lista& operator=(Lista&& o) noexcept {
        if (this != &o) {
            vaciar();
            inicio = o.inicio; tam = o.tam;
            o.inicio = nullptr; o.tam = 0;
        }
        return *this;
    }

    // O(1)
    bool     vacia()   const noexcept { return tam == 0; }
    size_t   size()    const noexcept { return tam; }

    // Inserciones
    void push_front (const T& dato)               { insertar(0, dato); }
    void push_back  (const T& dato);
    void insertar   (size_t pos, const T& dato);

    // Borrado
    void erase(size_t pos);

    // Acceso
    const T& at(size_t pos)  const;
    T&       at(size_t pos);

    // Utilidades
    void vaciar();
    void imprimir() const;

    Nodo<T>* getInicio() const noexcept { return inicio; }

   private:
    Nodo<T>* inicio;
    size_t   tam;

    void copiarDe(const Lista&);
};

// ---------- Implementación ------------

template <class T>
void Lista<T>::copiarDe(const Lista& o) {
    if (o.inicio == nullptr) { inicio = nullptr; tam = 0; return; }
    // Copia profunda
    inicio = new Nodo<T>(o.inicio->getDato());
    Nodo<T>* dst = inicio;
    for (Nodo<T>* src = o.inicio->getSig(); src; src = src->getSig()) {
        dst->setSig(new Nodo<T>(src->getDato()));
        dst = dst->getSig();
    }
    tam = o.tam;
}

template <class T>
void Lista<T>::insertar(size_t pos, const T& dato) {
    assert(pos <= tam);           // debug only
    if (pos == 0) {               // insertar al inicio
        inicio = new Nodo<T>(dato, inicio);
    } else {
        Nodo<T>* prev = inicio;
        for (size_t i = 0; i < pos - 1; ++i) prev = prev->getSig();
        prev->setSig(new Nodo<T>(dato, prev->getSig()));
    }
    ++tam;
}

template <class T>
void Lista<T>::push_back(const T& dato) {
    insertar(tam, dato);
}

template <class T>
void Lista<T>::erase(size_t pos) {
    assert(pos < tam);
    Nodo<T>* aBorrar;
    if (pos == 0) {
        aBorrar = inicio;
        inicio  = inicio->getSig();
    } else {
        Nodo<T>* prev = inicio;
        for (size_t i = 0; i < pos - 1; ++i) prev = prev->getSig();
        aBorrar = prev->getSig();
        prev->setSig(aBorrar->getSig());
    }
    delete aBorrar;
    --tam;
}

template <class T>
const T& Lista<T>::at(size_t pos) const {
    assert(pos < tam);
    Nodo<T>* aux = inicio;
    for (size_t i = 0; i < pos; ++i) aux = aux->getSig();
    return aux->getDato();
}
template <class T>
T& Lista<T>::at(size_t pos) {
    return const_cast<T&>(static_cast<const Lista<T>&>(*this).at(pos));
}

template <class T>
void Lista<T>::vaciar() {
    while (inicio) { Nodo<T>* nxt = inicio->getSig(); delete inicio; inicio = nxt; }
    tam = 0;
}

template <class T>
void Lista<T>::imprimir() const {
    for (Nodo<T>* n = inicio; n; n = n->getSig())
        std::cout << n->getDato() << " -> ";
    std::cout << "NULL\n";
}

#endif  // LISTA_H
