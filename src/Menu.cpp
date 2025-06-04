#include "Menu.h"
#include <iostream>
#include <string>
#include <functional>
#include <map>

#include "Lista.h"
#include "HashMapList.h"
#include "Venta.h"
#include "Pila.h"
#include "Utilidades.h"
#include "ProcesadorCSV.h"
#include "Modificaciones.h"
#include "Consultas.h"

using namespace std;

void mostrarMenu() {
    Lista<Venta> ventas;
    HashMapList<string, Venta> ventasPorPais(50);
    Pila<Venta> pilaDeshacer;
    Utilidades util;

    map<string, function<void()>> acciones;

    acciones["1"] = [&]() {
        util.start();
        cargarCSV("data/ventas_sudamerica.csv", ventas, ventasPorPais);
        util.end("Cargar CSV", "Lista + HashMapList", "O(n)");
        cout << "\nVentas cargadas: " << ventas.contar() << "\n";
    };

    acciones["2"] = [&]() {
        string pais;
        cout << "Ingrese el país: ";
        getline(cin, pais);
        mostrarVentasPorPais(pais, ventasPorPais);
    };

    acciones["3"] = [&]() {
        agregarVenta(ventas, ventasPorPais, pilaDeshacer);
    };

    acciones["4"] = [&]() {
        eliminarVentasPorCiudad(ventas, ventasPorPais, pilaDeshacer);
    };

    acciones["5"] = [&]() {
        deshacerUltimaOperacion(ventas, ventasPorPais, pilaDeshacer);
    };

    acciones["0"] = [&]() {
        cout << "Saliendo...\n";
    };

    while (true) {
        cout << "\n===== Menú de Ventas Sudamérica =====\n";
        cout << "1) Cargar CSV\n";
        cout << "2) Mostrar ventas por país\n";
        cout << "3) Agregar venta\n";
        cout << "4) Eliminar ventas por ciudad\n";
        cout << "5) Deshacer última operación\n";
        cout << "0) Salir\n";
        cout << "Seleccione opción: ";

        string opcion;
        getline(cin, opcion);

        auto it = acciones.find(opcion);
        if (it != acciones.end()) {
            if (opcion == "0") break;
            it->second();
        } else {
            cout << "Opción inválida. Intente nuevamente.\n";
        }
    }
}
