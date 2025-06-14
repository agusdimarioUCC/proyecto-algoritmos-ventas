#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "hashMapList.h"
#include "venta.h"
#include "procesador_de_csv.h"
#include "gestion_ventas.h"
using namespace std;

// Declaración de las variables globales (definidas en main.cpp)
extern vector<Venta> ventas;
extern HashMapList<int, Venta> mapaVentas;

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

    // Descartar el encabezado
    getline(archivo, linea);

    ventas.clear(); // Limpiamos el vector antes de cargar nuevos datos
    size_t total = 0;
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

        ventas.push_back(v);
        ++total;
    }

    archivo.close();
    cout << "Se cargaron " << total << " ventas en memoria." << endl;

    // Construir el mapa hash después de cargar todas las ventas
    construirHash(ventas, mapaVentas);
}
