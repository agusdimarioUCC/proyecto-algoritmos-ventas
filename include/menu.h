#ifndef MENU_H
#define MENU_H

#include <vector>
#include "hashMapList.h"
#include "venta.h"

// Funciones de menú
void menuPrincipal(std::vector<Venta>& ventas, HashMapList<int, Venta>& mapaVentas);
void menuAnalisis(HashMapList<int, Venta>& mapaVentas);

#endif // MENU_H
