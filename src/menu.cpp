#include <iostream>
#include <string>
#include "menu.h"
#include "analisis_ventas.h"
#include "gestion_ventas.h"
using namespace std;

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
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: top5CiudadesPorPais(mapaVentas);
            break;
        case 2: montoPorProductoPorPais(mapaVentas);
            break;
        case 3: promedioPorCategoriaPorPais(mapaVentas);
            break;
        case 4: medioEnvioMasUsadoPorPais(mapaVentas);
            break;
        case 5: medioEnvioMasUsadoPorCategoria(mapaVentas);
            break;
        case 6: diaMayorMonto(mapaVentas);
            break;
        case 7: estadoEnvioMasFrecuentePorPais(mapaVentas);
            break;
        case 8: productoMasVendido(mapaVentas);
            break;
        case 9: productoMenosVendido(mapaVentas);
            break;
        case 10: {
                string pais1, pais2;
                cout << "Ingrese el primer país: ";
                cin >> ws;
                getline(cin, pais1);
                cout << "Ingrese el segundo país: ";
                getline(cin, pais2);
                compararPaises(mapaVentas, pais1, pais2);
            }
            break;
        case 11: {
                string prod1, prod2;
                cout << "Ingrese el primer producto: ";
                cin >> ws;
                getline(cin, prod1);
                cout << "Ingrese el segundo producto: ";
                getline(cin, prod2);
                compararProductos(mapaVentas, prod1, prod2);
            }
            break;
        case 12: {
                string pais;
                double umbral;
                cout << "Ingrese el país: ";
                cin >> ws;
                getline(cin, pais);
                cout << "Ingrese el umbral de precio: ";
                cin >> umbral;
                productosPromedioPorDebajo(mapaVentas, pais, umbral);
            }
            break;
        case 13: {
                double umbral;
                cout << "Ingrese el umbral de precio: ";
                cin >> umbral;
                productosPromedioPorEncima(mapaVentas, umbral);
            }
            break;
        case 14: cout << "Volviendo al menú principal...\n";
            break;
        default: cout << "Opción inválida.\n";
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
        cout << "Seleccione una opción: ";
        cin >> opcion;

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
        default: cout << "Opción inválida.\n";
        }
    } while (opcion != 5);
}
