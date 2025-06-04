#ifndef ESTRUCTURAS_GLOBALES_H
#define ESTRUCTURAS_GLOBALES_H

#include "HashMap.h"
#include "HashMapList.h"
#include "Lista.h"
#include "Pila.h"
#include "Venta.h"

// Definiciones de alias para facilitar el uso

// Mapa principal: ID_Venta -> Venta
using MapaVentas = HashMap<string, Venta>;

// Lista de IDs para mantener orden de carga
using ListaIDs = Lista<string>;

// Top 5 ciudades por país: País -> (Ciudad -> Monto_total acumulado)
using MapaCiudadMonto = HashMap<string, float>;
using TopCiudadesPorPais = HashMapList<string, MapaCiudadMonto>;

// Monto total por producto por país: País -> (Producto -> Monto_total acumulado)
using MapaProductoMonto = HashMap<string, float>;
using ProductoPorPais = HashMapList<string, MapaProductoMonto>;

// Promedio ventas por categoría: País -> (Categoría -> (sumaMonto, cantidadVentas))
using ParMontoCantidad = pair<float, int>;
using MapaCategoriaPar = HashMap<string, ParMontoCantidad>;
using CategoriaPorPais = HashMapList<string, MapaCategoriaPar>;

// Medio de envío por país y por categoría: ambos valores enteros contadores
using MapaEnvios = HashMap<string, int>;
using EnviosPorPais = HashMapList<string, MapaEnvios>;
using EnviosPorCategoria = HashMapList<string, MapaEnvios>;

// Ventas por día (DD-MM-YYYY): Dia -> Monto_total acumulado
using MapaDiaMonto = HashMap<string, float>;

// Estado de envío por país: País -> (Estado -> Cantidad)
using MapaEstadoCant = HashMap<string, int>;
using EstadoPorPais = HashMapList<string, MapaEstadoCant>;

// Producto vendido en cantidad: Producto -> Cantidad_total
using MapaProductoCant = HashMap<string, int>;

#endif // ESTRUCTURAS_GLOBALES_H
