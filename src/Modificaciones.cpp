#include "Modificaciones.h"
#include <iostream>
using namespace std;

void agregarVenta(Lista<Venta>& ventas, HashMapList<string, Venta>& ventasPorPais, Pila<Venta>& pila)
{
	string id, fecha, pais, ciudad, cliente, producto, categoria, medio, estado;
	int cantidad;
	float precio, monto;

	cout << "ID Venta: ";
	getline(cin, id);
	cout << "Fecha (DD-MM-YYYY): ";
	getline(cin, fecha);
	cout << "País: ";
	getline(cin, pais);
	cout << "Ciudad: ";
	getline(cin, ciudad);
	cout << "Cliente: ";
	getline(cin, cliente);
	cout << "Producto: ";
	getline(cin, producto);
	cout << "Categoría: ";
	getline(cin, categoria);
	cout << "Cantidad: ";
	cin >> cantidad;
	cin.ignore();
	cout << "Precio unitario: ";
	cin >> precio;
	cin.ignore();
	monto = cantidad * precio;
	cout << "Medio de envío: ";
	getline(cin, medio);
	cout << "Estado de envío: ";
	getline(cin, estado);

	Venta nueva(id, fecha, pais, ciudad, cliente, producto, categoria, cantidad, precio, monto, medio, estado);
	ventas.insertarUltimo(nueva);
	ventasPorPais.put(pais, nueva);
	pila.push(nueva);

	cout << "Venta agregada.\n";
}

void eliminarVentasPorCiudad(Lista<Venta>& ventas, HashMapList<string, Venta>& ventasPorPais, Pila<Venta>& pila)
{
	string ciudad;
	cout << "Ingrese la ciudad de las ventas a eliminar: ";
	getline(cin, ciudad);

	Lista<Venta> ventasFiltradas;
	int largo = ventas.getTamanio();
	Nodo<Venta>* actual = ventas.getInicio();
	while (actual != nullptr)
	{
		Venta v = actual->getDato();
		if (v.ciudad == ciudad)
		{
			pila.push(v);
		}
		else
		{
			ventasFiltradas.insertarUltimo(v);
		}
		actual = actual->getSiguiente();
	}
	ventas = ventasFiltradas;

	ventasPorPais = HashMapList<string, Venta>(50);
	actual = ventas.getInicio();
	while (actual != nullptr)
	{
		Venta v = actual->getDato();
		ventasPorPais.put(v.pais, v);
		actual = actual->getSiguiente();
	}

	cout << "Ventas de la ciudad eliminadas.\n";
}

void deshacerUltimaOperacion(Lista<Venta>& ventas, HashMapList<string, Venta>& ventasPorPais, Pila<Venta>& pila)
{
	if (pila.esVacia())
	{
		cout << "No hay operaciones para deshacer.\n";
		return;
	}

	Venta ultima = pila.pop();
	ventas.insertarUltimo(ultima);
	ventasPorPais.put(ultima.pais, ultima);
	cout << "Se deshizo la última operación.\n";
}
