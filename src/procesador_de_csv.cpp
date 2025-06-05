#include <fstream>
#include <iostream>
#include <sstream>
#include "lector_csv.h"

using namespace std;

void procesarArchivoCSV(const string& nombreArchivo)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    char delimitador = ',';
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(archivo, linea);
    // Leemos todas las líneas
    while (getline(archivo, linea))
    {
        stringstream stream(linea); // Convertir la cadena a un stream
        string ID_Venta, Fecha, País, Ciudad, Cliente, Producto, Categoría, Cantidad, Precio_Unitario, Monto_Total,
                Medio_Envio, Estado_Envio;
        // Extraer todos los valores de esa fila
        getline(stream, ID_Venta, delimitador);
        getline(stream, Fecha, delimitador);
        getline(stream, País, delimitador);
        getline(stream, Ciudad, delimitador);
        getline(stream, Cliente, delimitador);
        getline(stream, Producto, delimitador);
        getline(stream, Categoría, delimitador);
        getline(stream, Cantidad, delimitador);
        getline(stream, Precio_Unitario, delimitador);
        getline(stream, Monto_Total, delimitador);
        getline(stream, Medio_Envio, delimitador);
        getline(stream, Estado_Envio, delimitador);
    }

    archivo.close();
    cout << "Procesamiento completado." << endl;
}