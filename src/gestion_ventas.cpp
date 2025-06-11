#include <algorithm>
#include <iostream>
#include <string>
#include "gestion_ventas.h"
#include "venta.h"
#include "hashMapList.h"
#include "contador_ifs.h"
using namespace std;

void construirHash(vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas) {
    mapaVentas.clear();
    for (int i = 0, n = ventas.size(); i < n; ++i) {
        const Venta& v = ventas[i];
        mapaVentas.put(v.idVenta, v);
    }
}

void agregarVenta(vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas) {
    iniciarConteoIfs();
    Venta nueva;
    string entrada;

    cout << "Ingrese los datos de la nueva venta:\n";

    try {
        cout << "ID: ";
        std::cin >> nueva.idVenta;

        do {
            cout << "Fecha (YYYY-MM-DD): ";
            getline(cin >> ws, nueva.fecha);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.fecha.empty()) break;
            cout << "La fecha no puede estar vacía.\n";
        } while (nueva.fecha.empty());

        do {
            cout << "País: ";
            getline(cin >> ws, nueva.pais);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.pais.empty()) break;
            cout << "El país no puede estar vacío.\n";
        } while (nueva.pais.empty());

        do {
            cout << "Ciudad: ";
            getline(cin >> ws, nueva.ciudad);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.ciudad.empty()) break;
            cout << "La ciudad no puede estar vacía.\n";
        } while (nueva.ciudad.empty());

        do {
            cout << "Cliente: ";
            getline(cin >> ws, nueva.cliente);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.cliente.empty()) break;
            cout << "El cliente no puede estar vacío.\n";
        } while (nueva.cliente.empty());

        do {
            cout << "Producto: ";
            getline(cin >> ws, nueva.producto);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.producto.empty()) break;
            cout << "El producto no puede estar vacío.\n";
        } while (nueva.producto.empty());

        do {
            cout << "Categoría: ";
            getline(cin >> ws, nueva.categoria);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.categoria.empty()) break;
            cout << "La categoría no puede estar vacía.\n";
        } while (nueva.categoria.empty());

        bool cantidadValida = false;
        do {
            cout << "Cantidad: ";
            getline(cin >> ws, entrada);
            try {
                nueva.cantidad = stoi(entrada);
                contadorIfs++; contadorIfsProceso++;
                if (nueva.cantidad > 0) {
                    cantidadValida = true;
                } else {
                    cout << "La cantidad debe ser un número mayor a 0.\n";
                }
            } catch (const invalid_argument&) {
                cout << "Ingrese un número entero válido.\n";
            } catch (const out_of_range&) {
                cout << "Número demasiado grande.\n";
            }
        } while (!cantidadValida);

        bool precioValido = false;
        do {
            cout << "Precio Unitario: ";
            getline(cin >> ws, entrada);
            try {
                nueva.precioUnitario = stof(entrada);
                contadorIfs++; contadorIfsProceso++;
                if (nueva.precioUnitario > 0) {
                    precioValido = true;
                } else {
                    cout << "El precio debe ser mayor a 0.\n";
                }
            } catch (const invalid_argument&) {
                cout << "Ingrese un número decimal válido.\n";
            } catch (const out_of_range&) {
                cout << "Número demasiado grande.\n";
            }
        } while (!precioValido);

        nueva.montoTotal = nueva.cantidad * nueva.precioUnitario;

        do {
            cout << "Medio de Envío: ";
            getline(cin >> ws, nueva.medioEnvio);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.medioEnvio.empty()) break;
            cout << "El medio de envío no puede estar vacío.\n";
        } while (nueva.medioEnvio.empty());

        do {
            cout << "Estado de Envío: ";
            getline(cin >> ws, nueva.estadoEnvio);
            contadorIfs++; contadorIfsProceso++;
            if (!nueva.estadoEnvio.empty()) break;
            cout << "El estado de envío no puede estar vacío.\n";
        } while (nueva.estadoEnvio.empty());

        ventas.push_back(nueva);
        construirHash(ventas, mapaVentas);

        cout << "\n>> Venta agregada con éxito.\n";
        cout << ">> Procesando estadísticas nuevamente...\n";
        mostrarEstadisticasProceso("Agregar venta");
    } catch (const exception& e) {
        cout << "Ocurrió un error inesperado al ingresar la venta: " << e.what() << "\n";
    }
}

void eliminarVenta(vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas) {
    iniciarConteoIfs();
    string filtro;

    do {
        cout << "Ingrese el país o ciudad de la venta a eliminar: ";
        getline(cin >> ws, filtro);
        contadorIfs++; contadorIfsProceso++;
        if (!filtro.empty()) break;
        cout << "El valor ingresado no puede estar vacío.\n";
    } while (filtro.empty());

    try {
        auto it = remove_if(ventas.begin(), ventas.end(), [&](Venta& v) {
            return v.pais == filtro || v.ciudad == filtro;
        });

        contadorIfs++; contadorIfsProceso++;
        if (it != ventas.end()) {
            ventas.erase(it, ventas.end());
            construirHash(ventas, mapaVentas);
            cout << "\nVentas eliminadas con éxito.\n";
            cout << ">> Reprocesando estadísticas...\n";
        } else {
            cout << "\nNo se encontraron ventas con ese país o ciudad.\n";
        }
        mostrarEstadisticasProceso("Eliminar venta");
    } catch (const exception& e) {
        cerr << "\nOcurrió un error inesperado al intentar eliminar ventas: " << e.what() << endl;
    }
}

void modificarVenta(vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas) {
    iniciarConteoIfs();
    int id;

    cout << "Ingrese el ID de la venta a modificar: ";
    std::cin >> id;

    auto it = find_if(ventas.begin(), ventas.end(), [&](Venta& v) {
        return v.idVenta == id;
    });

    contadorIfs++; contadorIfsProceso++;
    if (it != ventas.end()) {
        cout << "\n--- Modificando Venta ID: " << it->idVenta << " ---\n";

        string entrada;

        do {
            cout << "Nuevo producto: ";
            getline(cin >> ws, it->producto);
            contadorIfs++; contadorIfsProceso++;
            if (!it->producto.empty()) break;
            cout << "El producto no puede estar vacío.\n";
        } while (it->producto.empty());

        bool cantidadValida = false;
        do {
            cout << "Nueva cantidad: ";
            getline(cin >> ws, entrada);
            try {
                it->cantidad = stoi(entrada);
                contadorIfs++; contadorIfsProceso++;
                if (it->cantidad > 0) {
                    cantidadValida = true;
                } else {
                    cout << "La cantidad debe ser mayor a 0.\n";
                }
            } catch (invalid_argument&) {
                cout << "Ingrese un número entero válido.\n";
            } catch (out_of_range&) {
                cout << "El número ingresado es demasiado grande.\n";
            }
        } while (!cantidadValida);

        bool precioValido = false;
        do {
            cout << "Nuevo precio unitario: ";
            getline(cin >> ws, entrada);
            try {
                it->precioUnitario = stof(entrada);
                contadorIfs++; contadorIfsProceso++;
                if (it->precioUnitario > 0) {
                    precioValido = true;
                } else {
                    cout << "El precio debe ser mayor a 0.\n";
                }
            } catch (invalid_argument&) {
                cout << "Ingrese un número decimal válido.\n";
            } catch (out_of_range&) {
                cout << "El número ingresado es demasiado grande.\n";
            }
        } while (!precioValido);

        it->montoTotal = it->cantidad * it->precioUnitario;

        construirHash(ventas, mapaVentas);

        cout << "\nVenta modificada con éxito.\n";
        cout << ">> Reprocesando estadísticas...\n";
        mostrarEstadisticasProceso("Modificar venta");
    } else {
        cout << "\nNo se encontró una venta con ese ID.\n";
    }
}