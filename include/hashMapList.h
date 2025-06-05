#ifndef HASHMAPLIST_H
#define HASHMAPLIST_H

#include <functional>
#include <vector>
#include "Lista.h"
#include "HashEntry.h"

template <class K, class T,
          class Hash = std::hash<K>>
class HashMapList {
   public:
    explicit HashMapList(size_t cap = 16,
                         float maxLoad = 0.75,
                         const Hash& h = Hash())
        : buckets(cap, nullptr),
          capacity(cap),
          loadMax(maxLoad),
          hasher(h),
          elemCount(0) {}

    ~HashMapList() { clear(); }

    // ——— API ———
    bool   empty()  const noexcept { return elemCount == 0; }
    size_t size()   const noexcept { return elemCount; }

    void put(const K& key, const T& val);
    bool remove(const K& key);
    /** Devuelve puntero al valor o nullptr si no existe */
    T*   get(const K& key);
    /** Versión que lanza si no existe */
    const T& at(const K& key) const;

    void clear();

    void print() const;

   private:
    using Bucket = Lista<HashEntry<K,T>>;

    std::vector<Bucket*> buckets;
    size_t  capacity;
    float   loadMax;
    Hash    hasher;
    size_t  elemCount;

    void rehash(size_t newCap);
    size_t indexFor(const K& key) const noexcept {
        return hasher(key) % capacity;
    }
};

// ----------- implementación -----------

template <class K, class T, class Hash>
void HashMapList<K,T,Hash>::put(const K& key, const T& val) {
    size_t idx = indexFor(key);
    if (!buckets[idx]) buckets[idx] = new Bucket();

    // buscar si ya existe
    for (size_t i = 0; i < buckets[idx]->size(); ++i) {
        if (buckets[idx]->at(i).key() == key) {
            buckets[idx]->at(i).setValue(val);
            return;   // actualizado
        }
    }
    buckets[idx]->push_back(HashEntry<K,T>(key, val));
    if (++elemCount > capacity * loadMax) rehash(capacity * 2);
}

template <class K, class T, class Hash>
bool HashMapList<K,T,Hash>::remove(const K& key) {
    size_t idx = indexFor(key);
    if (!buckets[idx]) return false;
    for (size_t i = 0; i < buckets[idx]->size(); ++i) {
        if (buckets[idx]->at(i).key() == key) {
            buckets[idx]->erase(i);
            --elemCount;
            return true;
        }
    }
    return false;
}

template <class K, class T, class Hash>
T* HashMapList<K,T,Hash>::get(const K& key) {
    size_t idx = indexFor(key);
    if (!buckets[idx]) return nullptr;
    for (size_t i = 0; i < buckets[idx]->size(); ++i)
        if (buckets[idx]->at(i).key() == key)
            return &buckets[idx]->at(i).value();
    return nullptr;
}

template <class K, class T, class Hash>
const T& HashMapList<K,T,Hash>::at(const K& key) const {
    auto* self = const_cast<HashMapList*>(this);
    if (T* v = self->get(key)) return *v;
    throw std::out_of_range("Key not found in HashMapList");
}

template <class K, class T, class Hash>
void HashMapList<K,T,Hash>::clear() {
    for (auto* b : buckets) { delete b; }
    buckets.assign(capacity, nullptr);
    elemCount = 0;
}

template <class K, class T, class Hash>
void HashMapList<K,T,Hash>::print() const {
    for (size_t i = 0; i < capacity; ++i) {
        if (!buckets[i] || buckets[i]->vacia()) continue;
        std::cout << "[" << i << "] ";
        for (size_t j = 0; j < buckets[i]->size(); ++j) {
            const auto& e = buckets[i]->at(j);
            std::cout << "(" << e.key() << ", " << e.value() << ") ";
        }
        std::cout << "\n";
    }
}

template <class K, class T, class Hash>
void HashMapList<K,T,Hash>::rehash(size_t newCap) {
    std::vector<Bucket*> old(std::move(buckets));
    buckets.assign(newCap, nullptr);
    capacity = newCap;
    elemCount = 0;  // se recalculará

    for (auto* b : old) {
        if (!b) continue;
        for (size_t i = 0; i < b->size(); ++i) {
            put(b->at(i).key(), b->at(i).value());
        }
        delete b;
    }
}

#endif  // HASHMAPLIST_H
