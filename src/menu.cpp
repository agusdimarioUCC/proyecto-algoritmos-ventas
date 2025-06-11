#include <iostream>
#include <string>
#include "menu.h"
#include "analisis_ventas.h"
#include "gestion_ventas.h"
#include "contador_ifs.h"
using namespace std;

// Funcion auxiliar para leer enteros de forma segura
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
                cout << "Error: Ingrese un numero entre " << minimo << " y " << maximo << ".\n";
            }
        } catch (const invalid_argument&) {
            cout << "Error: Ingrese solo numeros.\n";
        } catch (const out_of_range&) {
            cout << "Error: El numero ingresado es demasiado grande.\n";
        }
    }
}

void menuAnalisis(HashMapList<int, Venta>& mapaVentas) {
    int opcion;
    do {
        cout << "\n--- MENÚ DE ANÁLISIS ---\n";
        cout << "1. Top 5 ciudades por pais\n";
        cout << "2. Monto por producto por pais\n";
        cout << "3. Promedio por categoria por pais\n";
        cout << "4. Medio de envio mas usado por pais\n";
        cout << "5. Medio de envio mas usado por categoria\n";
        cout << "6. Dia con mayor monto de ventas\n";
        cout << "7. Estado de envio mas frecuente por pais\n";
        cout << "8. Producto mas vendido\n";
        cout << "9. Producto menos vendido\n";
        cout << "10. Comparar paises\n";
        cout << "11. Comparar productos\n";
        cout << "12. Productos bajo umbral de precio\n";
        cout << "13. Productos sobre umbral de precio\n";
        cout << "14. Volver al menu principal\n";

        opcion = leerEnteroSeguro("Seleccione una opcion: ", 1, 14);

        iniciarConteoIfs(); // Iniciar conteo para cada analisis

        switch (opcion) {
        case 1:
            top5CiudadesPorPais(mapaVentas);
            mostrarEstadisticasProceso("Top 5 ciudades por pais");
            break;
        case 2:
            montoPorProductoPorPais(mapaVentas);
            mostrarEstadisticasProceso("Monto por producto por pais");
            break;
        case 3:
            promedioPorCategoriaPorPais(mapaVentas);
            mostrarEstadisticasProceso("Promedio por categoria por pais");
            break;
        case 4:
            medioEnvioMasUsadoPorPais(mapaVentas);
            mostrarEstadisticasProceso("Medio de envio mas usado por pais");
            break;
        case 5:
            medioEnvioMasUsadoPorCategoria(mapaVentas);
            mostrarEstadisticasProceso("Medio de envio mas usado por categoria");
            break;
        case 6:
            diaMayorMonto(mapaVentas);
            mostrarEstadisticasProceso("Dia con mayor monto de ventas");
            break;
        case 7:
            estadoEnvioMasFrecuentePorPais(mapaVentas);
            mostrarEstadisticasProceso("Estado de envio mas frecuente por pais");
            break;
        case 8:
            productoMasVendido(mapaVentas);
            mostrarEstadisticasProceso("Producto mas vendido");
            break;
        case 9:
            productoMenosVendido(mapaVentas);
            mostrarEstadisticasProceso("Producto menos vendido");
            break;
        case 10: {
                string pais1, pais2;
                cout << "Ingrese el primer pais: ";
                getline(cin, pais1);
                cout << "Ingrese el segundo pais: ";
                getline(cin, pais2);
                compararPaises(mapaVentas, pais1, pais2);
                mostrarEstadisticasProceso("Comparacion de paises");
            }
            break;
        case 11: {
                string prod1, prod2;
                cout << "Ingrese el primer producto: ";
                getline(cin, prod1);
                cout << "Ingrese el segundo producto: ";
                getline(cin, prod2);
                compararProductos(mapaVentas, prod1, prod2);
                mostrarEstadisticasProceso("Comparacion de productos");
            }
            break;
        case 12: {
                string pais;
                double umbral;
                cout << "Ingrese el pais: ";
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
            cout << "Volviendo al menu principal...\n";
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
        cout << "4. Ver analisis de ventas\n";
        cout << "5. Salir\n";

        opcion = leerEnteroSeguro("Seleccione una opcion: ", 1, 5);

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