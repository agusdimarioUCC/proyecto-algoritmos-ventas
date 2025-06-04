#ifndef MODIFICACIONES_H
#define MODIFICACIONES_H

#include "Venta.h"
#include "Lista.h"
#include "HashMapList.h"
#include "Pila.h"
#include <string>

void agregarVenta(Lista<Venta>& ventas, HashMapList<std::string, Venta>& ventasPorPais, Pila<Venta>& pila);
void eliminarVentasPorCiudad(Lista<Venta>& ventas, HashMapList<std::string, Venta>& ventasPorPais, Pila<Venta>& pila);
void deshacerUltimaOperacion(Lista<Venta>& ventas, HashMapList<std::string, Venta>& ventasPorPais, Pila<Venta>& pila);

#endif // MODIFICACIONES_H
