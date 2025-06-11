#ifndef LISTA_H
#define LISTA_H

#include <cassert>
#include <iostream>
#include "Nodo.h"

/**
 * Lista enlazada genérica simple.
 * Mantiene un contador interno -> getTamanio() es O(1).
 */
template <class T>
class Lista
{
private:
	Nodo<T>* inicio;
	size_t tam; // NUEVO: tamaño en O(1)

	void copiarDe(const Lista& o)
	{
		if (!o.inicio)
		{
			inicio = nullptr;
			tam = 0;
			return;
		}
		inicio = new Nodo<T>(o.inicio->getDato());
		Nodo<T>* dst = inicio;
		for (Nodo<T>* src = o.inicio->getSiguiente(); src; src = src->getSiguiente())
		{
			dst->setSiguiente(new Nodo<T>(src->getDato()));
			dst = dst->getSiguiente();
		}
		tam = o.tam;
	}

public:
	Lista() noexcept : inicio(nullptr), tam(0)
	{
	}

	// Regla de los 5
	~Lista() { vaciar(); }
	Lista(const Lista& o) { copiarDe(o); }

	Lista& operator=(const Lista& o)
	{
		if (this != &o)
		{
			vaciar();
			copiarDe(o);
		}
		return *this;
	}

	Lista(Lista&& o) noexcept : inicio(o.inicio), tam(o.tam)
	{
		o.inicio = nullptr;
		o.tam = 0;
	}

	Lista& operator=(Lista&& o) noexcept
	{
		if (this != &o)
		{
			vaciar();
			inicio = o.inicio;
			tam = o.tam;
			o.inicio = nullptr;
			o.tam = 0;
		}
		return *this;
	}

	// ---- API con nombres ORIGINALES ----
	bool esVacia() const noexcept { return tam == 0; }
	int getTamanio() const noexcept { return static_cast<int>(tam); }

	void insertar(int pos, T dato)
	{
		assert(pos >= 0 && static_cast<size_t>(pos) <= tam);
		if (pos == 0)
		{
			inicio = new Nodo<T>(std::move(dato), inicio);
		}
		else
		{
			Nodo<T>* prev = inicio;
			for (int i = 0; i < pos - 1; ++i) prev = prev->getSiguiente();
			prev->setSiguiente(new Nodo<T>(std::move(dato), prev->getSiguiente()));
		}
		++tam;
	}

	void insertarPrimero(T dato) { insertar(0, std::move(dato)); }
	void insertarUltimo(T dato) { insertar(getTamanio(), std::move(dato)); }

	void remover(int pos)
	{
		assert(pos >= 0 && pos < getTamanio());
		Nodo<T>* aBorrar;
		if (pos == 0)
		{
			aBorrar = inicio;
			inicio = inicio->getSiguiente();
		}
		else
		{
			Nodo<T>* prev = inicio;
			for (int i = 0; i < pos - 1; ++i) prev = prev->getSiguiente();
			aBorrar = prev->getSiguiente();
			prev->setSiguiente(aBorrar->getSiguiente());
		}
		delete aBorrar;
		--tam;
	}

	T& getDato(int pos)
	{
		assert(pos >= 0 && pos < getTamanio());
		Nodo<T>* aux = inicio;
		for (int i = 0; i < pos; ++i) aux = aux->getSiguiente();
		return aux->getDato();
	}

	const T& getDato(int pos) const { return const_cast<Lista*>(this)->getDato(pos); }

	void reemplazar(int pos, T dato) { getDato(pos) = std::move(dato); }

	void vaciar()
	{
		while (inicio)
		{
			Nodo<T>* nxt = inicio->getSiguiente();
			delete inicio;
			inicio = nxt;
		}
		tam = 0;
	}

	void imprimir() const
	{
		Nodo<T>* aux = inicio;
		while (aux)
		{
			std::cout << aux->getDato() << "->";
			aux = aux->getSiguiente();
		}
		std::cout << "NULL\n";
	}

	// Función utilitaria extra de tu profe
	void insertAfter2(int oldValue, int n, int newValue)
	{
		Nodo<T>* aux = inicio;
		int contador = 0, posActual = 0;
		while (aux)
		{
			if (aux->getDato() == oldValue)
			{
				contador++;
				if (contador == n)
				{
					insertar(posActual + 1, newValue);
					return;
				}
			}
			aux = aux->getSiguiente();
			++posActual;
		}
	}

	Nodo<T>* getInicio() const noexcept { return inicio; }
};

#endif  // LISTA_H
