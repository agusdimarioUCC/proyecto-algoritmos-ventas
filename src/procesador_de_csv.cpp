#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "lector_csv.h"

using namespace std;

struct Venta
{
	int idVenta{};
	string fecha;
	string pais;
	string ciudad;
	string cliente;
	string producto;
	string categoria;
	int cantidad{};
	double precioUnitario{};
	double montoTotal{};
	string medioEnvio;
	string estadoEnvio;
};

// Vector global que almacena todas las ventas leídas del CSV
static vector<Venta> ventas;

void procesarArchivoCSV(const string& nombreArchivo)
{
	ifstream archivo(nombreArchivo);
	if (!archivo.is_open())
	{
		cout << "Error al abrir el archivo: " << nombreArchivo << endl;
		return;
	}

	string linea;
	const char delimitador = ',';

	// Descartar encabezado
	getline(archivo, linea);

	// Leer cada línea del archivo
	while (getline(archivo, linea))
	{
		stringstream stream(linea);

		string id, fecha, pais, ciudad, cliente, producto, categoria,
				cantidad, precioUnitario, montoTotal, medioEnvio, estadoEnvio;

		getline(stream, id, delimitador);
		getline(stream, fecha, delimitador);
		getline(stream, pais, delimitador);
		getline(stream, ciudad, delimitador);
		getline(stream, cliente, delimitador);
		getline(stream, producto, delimitador);
		getline(stream, categoria, delimitador);
		getline(stream, cantidad, delimitador);
		getline(stream, precioUnitario, delimitador);
		getline(stream, montoTotal, delimitador);
		getline(stream, medioEnvio, delimitador);
		getline(stream, estadoEnvio, delimitador);

		Venta v;
		v.idVenta = stoi(id);
		v.fecha = fecha;
		v.pais = pais;
		v.ciudad = ciudad;
		v.cliente = cliente;
		v.producto = producto;
		v.categoria = categoria;
		v.cantidad = stoi(cantidad);
		v.precioUnitario = stod(precioUnitario);
		v.montoTotal = stod(montoTotal);
		v.medioEnvio = medioEnvio;
		v.estadoEnvio = estadoEnvio;

		ventas.push_back(std::move(v));
	}

	archivo.close();
}
