#ifndef HASHENTRY_H
#define HASHENTRY_H

template <class K, class T>
class HashEntry
{
private:
    K clave;
    T valor;

public:
    HashEntry(const K& c, const T& v) : clave(c), valor(v)
    {
    }

    const K& getClave() const noexcept { return clave; }
    K& getClave() noexcept { return clave; }

    const T& getValor() const noexcept { return valor; }
    T& getValor() noexcept { return valor; }

    void setValor(const T& v) noexcept { valor = v; }
};

#endif  // HASHENTRY_H
