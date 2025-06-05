#ifndef HASHMAPLIST_H
#define HASHMAPLIST_H

#include <functional>
#include <vector>
#include <iostream>
#include "Lista.h"
#include "HashEntry.h"

/**
 * Tabla hash (chaining con Lista).
 * Mantiene interfaz original: put, get, remove, esVacio, print, getList.
 */
template <class K, class T,
		class Hash = std::hash<K>>
class HashMapList
{
private:
	using Bucket = Lista<HashEntry<K, T>>;

	std::vector<Bucket*> buckets;
	size_t capacidad;
	size_t elementos;
	float factorCargaMax;
	Hash hasher;

	size_t indexFor(const K& clave) const noexcept
	{
		return hasher(clave) % capacidad;
	}

	void rehash(size_t nuevaCap);

public:
	explicit HashMapList(size_t cap = 16,
						float carga = 0.75,
						const Hash& h = Hash())
		: buckets(cap, nullptr),
		capacidad(cap),
		elementos(0),
		factorCargaMax(carga),
		hasher(h)
	{
	}

	~HashMapList() { clear(); }

	// ---- nombres originales ----
	void put(K clave, T valor);
	void remove(K clave);
	T get(K clave); // lanza 404 si no existe
	bool esVacio() const noexcept { return elementos == 0; }
	void getList(K clave);
	void print() const;
	void clear();
};

/*----------- implementación -----------*/

template <class K, class T, class Hash>
void HashMapList<K, T, Hash>::put(K clave, T valor)
{
	size_t idx = indexFor(clave);
	if (!buckets[idx]) buckets[idx] = new Bucket();

	// actualizar si ya existe
	for (int i = 0; i < buckets[idx]->getTamanio(); ++i)
	{
		if (buckets[idx]->getDato(i).getClave() == clave)
		{
			buckets[idx]->getDato(i).setValor(std::move(valor));
			return;
		}
	}
	buckets[idx]->insertarUltimo(HashEntry<K, T>(std::move(clave), std::move(valor)));
	if (++elementos > capacidad * factorCargaMax) rehash(capacidad * 2);
}

template <class K, class T, class Hash>
void HashMapList<K, T, Hash>::remove(K clave)
{
	size_t idx = indexFor(clave);
	if (!buckets[idx]) throw 404;

	for (int i = 0; i < buckets[idx]->getTamanio(); ++i)
	{
		if (buckets[idx]->getDato(i).getClave() == clave)
		{
			buckets[idx]->remover(i);
			--elementos;
			return;
		}
	}
	throw 404; // no estaba
}

template <class K, class T, class Hash>
T HashMapList<K, T, Hash>::get(K clave)
{
	size_t idx = indexFor(clave);
	if (!buckets[idx]) throw 404;

	for (int i = 0; i < buckets[idx]->getTamanio(); ++i)
	{
		if (buckets[idx]->getDato(i).getClave() == clave)
			return buckets[idx]->getDato(i).getValor();
	}
	throw 404;
}

template <class K, class T, class Hash>
void HashMapList<K, T, Hash>::getList(K clave)
{
	size_t idx = indexFor(clave);
	if (!buckets[idx]) throw 404;
	Nodo<HashEntry<K, T>>* aux = buckets[idx]->getInicio();
	while (aux)
	{
		std::cout << aux->getDato().getValor() << '\n';
		aux = aux->getSiguiente();
	}
}

template <class K, class T, class Hash>
void HashMapList<K, T, Hash>::print() const
{
	for (size_t i = 0; i < capacidad; ++i)
	{
		if (!buckets[i] || buckets[i]->esVacia()) continue;
		std::cout << "[" << i << "] ";
		Nodo<HashEntry<K, T>>* n = buckets[i]->getInicio();
		while (n)
		{
			std::cout << "(" << n->getDato().getClave() << ", "
				<< n->getDato().getValor() << ") ";
			n = n->getSiguiente();
		}
		std::cout << '\n';
	}
}

template <class K, class T, class Hash>
void HashMapList<K, T, Hash>::clear()
{
	for (auto* b : buckets) delete b;
	buckets.assign(capacidad, nullptr);
	elementos = 0;
}

template <class K, class T, class Hash>
void HashMapList<K, T, Hash>::rehash(size_t nuevaCap)
{
	std::vector<Bucket*> old(std::move(buckets));
	buckets.assign(nuevaCap, nullptr);
	capacidad = nuevaCap;
	elementos = 0;
	for (auto* b : old)
	{
		if (!b) continue;
		Nodo<HashEntry<K, T>>* n = b->getInicio();
		while (n)
		{
			put(n->getDato().getClave(), n->getDato().getValor());
			n = n->getSiguiente();
		}
		delete b;
	}
}

#endif  // HASHMAPLIST_H
