#ifndef HASHENTRY_H
#define HASHENTRY_H

template <class K, class T>
class HashEntry {
public:
    HashEntry(const K& c, const T& v) : clave(c), valor(v) {}

    const K& key()   const noexcept { return clave; }
    const T& value() const noexcept { return valor; }
    T& value()       noexcept { return valor; }

    void setValue(const T& v) noexcept { valor = v; }

private:
    K clave;
    T valor;
};

#endif  // HASHENTRY_H
