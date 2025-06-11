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

    // Iniciar el menú principal
    menuPrincipal(ventas, mapaVentas);

    return 0;
}
