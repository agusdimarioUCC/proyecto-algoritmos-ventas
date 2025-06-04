#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <string>
#include "Venta.h"
#include "HashMapList.h"

void mostrarVentasPorPais(const std::string& pais, HashMapList<std::string, Venta>& ventasPorPais);

#endif // CONSULTAS_H
