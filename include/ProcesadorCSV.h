#ifndef PROCESADORCSV_H
#define PROCESADORCSV_H

#include <string>
#include "HashMapList.h"
#include "Lista.h"
#include "Venta.h"
using namespace std;
void cargarCSV(const string& rutaArchivo, Lista<Venta>& ventas, HashMapList<string, Venta>& ventasPorPais);

#endif // PROCESADORCSV_H
