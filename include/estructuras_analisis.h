#ifndef ESTRUCTURAS_ANALISIS_H
#define ESTRUCTURAS_ANALISIS_H

#include <string>

// Estructuras auxiliares para ordenar y analizar datos
struct CiudadMonto
{
	std::string ciudad;
	double monto;

	CiudadMonto(const std::string& c, double m) : ciudad(c), monto(m) {}
};

struct ProductoMonto
{
	std::string producto;
	double monto;

	ProductoMonto(const std::string& p, double m) : producto(p), monto(m) {}
};

struct CategoriaProm
{
	std::string categoria;
	double prom;

	CategoriaProm(const std::string& c, double p) : categoria(c), prom(p) {}
};

struct MedioCont
{
	std::string medio;
	int cont;

	MedioCont(const std::string& m, int c) : medio(m), cont(c) {}
};

struct EstadoCont
{
	std::string estado;
	int cont;

	EstadoCont(const std::string& e, int c) : estado(e), cont(c) {}
};

struct DiaMonto
{
	std::string dia;
	double monto;

	DiaMonto(const std::string& d, double m) : dia(d), monto(m) {}
};

struct ProductoCant
{
	std::string producto;
	int cant;

	ProductoCant(const std::string& p, int c) : producto(p), cant(c) {}
};

#endif // ESTRUCTURAS_ANALISIS_H
