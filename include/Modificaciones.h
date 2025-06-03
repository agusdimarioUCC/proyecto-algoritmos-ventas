#ifndef MODIFICACIONES_H
#define MODIFICACIONES_H

#include <string>
#include "EstructurasGlobales.h"
#include "Utilidades.h"

// Agrega una nueva venta solicitando datos al usuario
void agregarVenta(
    Utilidades &utilidades,
    MapaVentas &mapaVentas,
    ListaIDs &listaIDs,
    TopCiudadesPorPais &topCiudadesPorPais,
    ProductoPorPais &productoPorPais,
    CategoriaPorPais &categoriaPorPais,
    EnviosPorPais &enviosPorPais,
    EnviosPorCategoria &enviosPorCategoria,
    MapaDiaMonto &diaMonto,
    EstadoPorPais &estadoPorPais,
    MapaProductoCant &productoCantidades,
    Pila<Venta> &pilaDeshacer
);

// Elimina una venta por ID (después de filtro por país o ciudad)
void eliminarVenta(
    Utilidades &utilidades,
    MapaVentas &mapaVentas,
    ListaIDs &listaIDs,
    TopCiudadesPorPais &topCiudadesPorPais,
    ProductoPorPais &productoPorPais,
    CategoriaPorPais &categoriaPorPais,
    EnviosPorPais &enviosPorPais,
    EnviosPorCategoria &enviosPorCategoria,
    MapaDiaMonto &diaMonto,
    EstadoPorPais &estadoPorPais,
    MapaProductoCant &productoCantidades,
    Pila<Venta> &pilaDeshacer
);

// Modifica una venta existente por ID
void modificarVenta(
    Utilidades &utilidades,
    MapaVentas &mapaVentas,
    ListaIDs &listaIDs,
    TopCiudadesPorPais &topCiudadesPorPais,
    ProductoPorPais &productoPorPais,
    CategoriaPorPais &categoriaPorPais,
    EnviosPorPais &enviosPorPais,
    EnviosPorCategoria &enviosPorCategoria,
    MapaDiaMonto &diaMonto,
    EstadoPorPais &estadoPorPais,
    MapaProductoCant &productoCantidades,
    Pila<Venta> &pilaDeshacer
);

// Deshace la última operación (usando la pila)
void deshacerOperacion(
    Utilidades &utilidades,
    MapaVentas &mapaVentas,
    ListaIDs &listaIDs,
    TopCiudadesPorPais &topCiudadesPorPais,
    ProductoPorPais &productoPorPais,
    CategoriaPorPais &categoriaPorPais,
    EnviosPorPais &enviosPorPais,
    EnviosPorCategoria &enviosPorCategoria,
    MapaDiaMonto &diaMonto,
    EstadoPorPais &estadoPorPais,
    MapaProductoCant &productoCantidades,
    Pila<Venta> &pilaDeshacer
);

#endif // MODIFICACIONES_H
