#ifndef PROCESADOR_CSV_H
#define PROCESADOR_CSV_H

#include <string>
#include <fstream>
#include <sstream>
#include "Venta.h"
#include "EstructurasGlobales.h"
#include "Utilidades.h"

void cargarYParsearCSV(
    const std::string &nombreArchivo,
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
    MapaProductoCant &productoCantidades
);

#endif // PROCESADOR_CSV_H
