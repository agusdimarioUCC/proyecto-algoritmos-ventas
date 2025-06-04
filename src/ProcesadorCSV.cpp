#include "ProcesadorCSV.h"
#include <fstream>
#include <sstream>

void cargarCSV(const std::string& rutaArchivo, Lista<Venta>& ventas, HashMapList<std::string, Venta>& ventasPorPais) {
    std::ifstream archivo(rutaArchivo);
    std::string linea;
    bool primera = true;

    while (std::getline(archivo, linea)) {
        if (primera) { primera = false; continue; }
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string campo;
        std::string datos[13];
        int i = 0;

        while (std::getline(ss, campo, ',') && i < 13) {
            datos[i++] = campo;
        }

        int cantidad = std::stoi(datos[7]);
        float precio = std::stof(datos[8]);
        float monto = std::stof(datos[9]);

        Venta v(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5], datos[6], cantidad, precio, monto, datos[10], datos[11]);

        ventas.insertarUltimo(v);
        ventasPorPais.put(datos[2], v); // datos[2] = país
    }
}
