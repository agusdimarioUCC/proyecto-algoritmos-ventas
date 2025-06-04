#ifndef PROCESADORCSV_H
#define PROCESADORCSV_H

#include <string>
#include "Venta.h"
#include "Lista.h"
#include "HashMapList.h"

void cargarCSV(const std::string& rutaArchivo, Lista<Venta>& ventas, HashMapList<std::string, Venta>& ventasPorPais);

#endif // PROCESADORCSV_H
