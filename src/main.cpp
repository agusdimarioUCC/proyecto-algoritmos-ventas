#include <vector>
#include <iostream>
#include "venta.h"
#include "menu.h"
#include "procesador_de_csv.h"

using namespace std;

// Variables globales
vector<Venta> ventas;
HashMapList<int, Venta> mapaVentas;

int main() {
    // Cargar los datos desde el archivo CSV
    procesarArchivoCSV("../data/ventas_sudamerica.csv");
    
    // DEBUG: Verificar si los datos se cargaron
    cout << "Ventas cargadas: " << ventas.size() << endl;
    cout << "Capacidad del mapa: " << mapaVentas.getcapacidad() << endl;
    
    // Contar elementos en el mapa
    int contador = 0;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (bucket) {
            auto* nodo = bucket->getInicio();
            while (nodo) {
                contador++;
                nodo = nodo->getSiguiente();
            }
        }
    }
    cout << "Elementos en el mapa: " << contador << endl;
    
    menuPrincipal(ventas, mapaVentas);
    return 0;
}