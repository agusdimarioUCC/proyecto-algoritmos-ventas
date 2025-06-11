#ifndef GESTION_VENTAS_H
#define GESTION_VENTAS_H

#include <vector>
#include "venta.h"
#include "hashMapList.h"

// Funciones de gestión de ventas
void construirHash(std::vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas);
void agregarVenta(std::vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas);
void eliminarVenta(std::vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas);
void modificarVenta(std::vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas);

#endif // GESTION_VENTAS_H
