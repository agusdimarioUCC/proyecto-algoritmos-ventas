#include <fstream>
#include <iostream>
#include <sstream>
#include "lector_csv.h"
#include "hashMapList.h"

using namespace std;

struct Venta
{
    int idVenta;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    double precioUnitario;
    double montoTotal;
    string medioEnvio;
    string estadoEnvio;
};

// HashMapList global:  clave = ID de venta, valor = struct Venta
static HashMapList<int, Venta> mapaVentas;

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

        mapaVentas.put(v.idVenta, std::move(v));
        ++total;
    }

    archivo.close();
    cout << "Se cargaron " << total << " ventas en memoria." << endl;
}
