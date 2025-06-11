#include <iostream>
#include <string>
#include <limits>
#include "menu.h"
#include "analisis_ventas.h"
#include "gestion_ventas.h"
#include "contador_ifs.h"
using namespace std;

// Función auxiliar para leer enteros de forma segura
int leerEnteroSeguro(const string& mensaje, int minimo, int maximo) {
    int valor;
    string entrada;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        try {
            valor = stoi(entrada);
            if (valor >= minimo && valor <= maximo) {
                return valor;
            } else {
                cout << "Error: Ingrese un número entre " << minimo << " y " << maximo << ".\n";
            }
        } catch (const invalid_argument&) {
            cout << "Error: Ingrese solo números.\n";
        } catch (const out_of_range&) {
            cout << "Error: El número ingresado es demasiado grande.\n";
        }
    }
}

void menuAnalisis(HashMapList<int, Venta>& mapaVentas) {
    int opcion;
    do {
        cout << "\n--- MENÚ DE ANÁLISIS ---\n";
        cout << "1. Top 5 ciudades por país\n";
        cout << "2. Monto por producto por país\n";
        cout << "3. Promedio por categoría por país\n";
        cout << "4. Medio de envío más usado por país\n";
        cout << "5. Medio de envío más usado por categoría\n";
        cout << "6. Día con mayor monto de ventas\n";
        cout << "7. Estado de envío más frecuente por país\n";
        cout << "8. Producto más vendido\n";
        cout << "9. Producto menos vendido\n";
        cout << "10. Comparar países\n";
        cout << "11. Comparar productos\n";
        cout << "12. Productos bajo umbral de precio\n";
        cout << "13. Productos sobre umbral de precio\n";
        cout << "14. Volver al menú principal\n";

        opcion = leerEnteroSeguro("Seleccione una opción: ", 1, 14);

        iniciarConteoIfs(); // Iniciar conteo para cada análisis

        switch (opcion) {
        case 1:
            top5CiudadesPorPais(mapaVentas);
            mostrarEstadisticasProceso("Top 5 ciudades por país");
            break;
        case 2:
            montoPorProductoPorPais(mapaVentas);
            mostrarEstadisticasProceso("Monto por producto por país");
            break;
        case 3:
            promedioPorCategoriaPorPais(mapaVentas);
            mostrarEstadisticasProceso("Promedio por categoría por país");
            break;
        case 4:
            medioEnvioMasUsadoPorPais(mapaVentas);
            mostrarEstadisticasProceso("Medio de envío más usado por país");
            break;
        case 5:
            medioEnvioMasUsadoPorCategoria(mapaVentas);
            mostrarEstadisticasProceso("Medio de envío más usado por categoría");
            break;
        case 6:
            diaMayorMonto(mapaVentas);
            mostrarEstadisticasProceso("Día con mayor monto de ventas");
            break;
        case 7:
            estadoEnvioMasFrecuentePorPais(mapaVentas);
            mostrarEstadisticasProceso("Estado de envío más frecuente por país");
            break;
        case 8:
            productoMasVendido(mapaVentas);
            mostrarEstadisticasProceso("Producto más vendido");
            break;
        case 9:
            productoMenosVendido(mapaVentas);
            mostrarEstadisticasProceso("Producto menos vendido");
            break;
        case 10: {
                string pais1, pais2;
                cout << "Ingrese el primer país: ";
                getline(cin, pais1);
                cout << "Ingrese el segundo país: ";
                getline(cin, pais2);
                compararPaises(mapaVentas, pais1, pais2);
                mostrarEstadisticasProceso("Comparación de países");
            }
            break;
        case 11: {
                string prod1, prod2;
                cout << "Ingrese el primer producto: ";
                getline(cin, prod1);
                cout << "Ingrese el segundo producto: ";
                getline(cin, prod2);
                compararProductos(mapaVentas, prod1, prod2);
                mostrarEstadisticasProceso("Comparación de productos");
            }
            break;
        case 12: {
                string pais;
                double umbral;
                cout << "Ingrese el país: ";
                getline(cin, pais);
                cout << "Ingrese el umbral de precio: ";
                cin >> umbral;
                cin.ignore(); // Limpiar el buffer después de cin
                productosPromedioPorDebajo(mapaVentas, pais, umbral);
                mostrarEstadisticasProceso("Productos bajo umbral de precio");
            }
            break;
        case 13: {
                double umbral;
                cout << "Ingrese el umbral de precio: ";
                cin >> umbral;
                cin.ignore(); // Limpiar el buffer después de cin
                productosPromedioPorEncima(mapaVentas, umbral);
                mostrarEstadisticasProceso("Productos sobre umbral de precio");
            }
            break;
        case 14:
            cout << "Volviendo al menú principal...\n";
            break;
        }
    } while (opcion != 14);
}

void menuPrincipal(vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas) {
    int opcion;
    do {
        cout << "\n--- MENÚ PRINCIPAL ---\n";
        cout << "1. Agregar venta\n";
        cout << "2. Eliminar venta\n";
        cout << "3. Modificar venta\n";
        cout << "4. Ver análisis de ventas\n";
        cout << "5. Salir\n";

        opcion = leerEnteroSeguro("Seleccione una opción: ", 1, 5);

        switch (opcion) {
        case 1: agregarVenta(ventas, mapaVentas);
            break;
        case 2: eliminarVenta(ventas, mapaVentas);
            break;
        case 3: modificarVenta(ventas, mapaVentas);
            break;
        case 4: menuAnalisis(mapaVentas);
            break;
        case 5: cout << "Saliendo...\n";
            break;
        }
    } while (opcion != 5);
}