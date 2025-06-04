#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <iostream>
using namespace std;
//pasamos el csv a un struct
struct Venta {
	int idVenta;
	string fecha;
	string pais;
	string ciudad;
	string cliente;
	string producto;
	string categoria;
	int cantidad;
	float precioUnitario;
	float montoTotal;
	string medioEnvio;
	string estadoEnvio;

	Venta() {}

	Venta(int id, string f, string p, string c, string cli, string prod, string cat,
		  int cant, float precio, float total, string medio, string estado) {
		idVenta = id;
		fecha = f;
		pais = p;
		ciudad = c;
		cliente = cli;
		producto = prod;
		categoria = cat;
		cantidad = cant;
		precioUnitario = precio;
		montoTotal = total;
		medioEnvio = medio;
		estadoEnvio = estado;
	}

	// Operador de salida para imprimir la venta
	friend ostream& operator<<(ostream& os, const Venta& v) {
		os << "ID: " << v.idVenta << ", Fecha: " << v.fecha << ", País: " << v.pais 
		   << ", Ciudad: " << v.ciudad << ", Cliente: " << v.cliente 
		   << ", Producto: " << v.producto << ", Monto: $" << v.montoTotal;
		return os;
	}
};

#endif // VENTA_H
