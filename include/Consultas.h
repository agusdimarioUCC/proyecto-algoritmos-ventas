#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <string>
#include "EstructurasGlobales.h"
#include "Utilidades.h"

void listarVentasPorCiudad(
    Utilidades &utilidades,
    const MapaVentas &mapaVentas,
    const ListaIDs &listaIDs,
    const std::string &ciudad
);

void listarVentasPorRangoFechasPorPais(
    Utilidades &utilidades,
    const MapaVentas &mapaVentas,
    const ListaIDs &listaIDs,
    const std::string &pais,
    const std::string &fechaInicio, // formato DD-MM-YYYY
    const std::string &fechaFin     // formato DD-MM-YYYY
);

void compararDosPaises(
    Utilidades &utilidades,
    const MapaVentas &mapaVentas,
    const ListaIDs &listaIDs,
    const std::string &pais1,
    const std::string &pais2
);

void compararDosProductosPorPais(
    Utilidades &utilidades,
    const MapaVentas &mapaVentas,
    const ListaIDs &listaIDs,
    const std::string &producto1,
    const std::string &producto2
);

void buscarProductosPorMontoPromedio(
    Utilidades &utilidades,
    const MapaVentas &mapaVentas,
    const ListaIDs &listaIDs,
    const std::string &pais,
    float umbral,
    bool buscarMayor // true: mayor a umbral, false: menor a umbral
);

#endif // CONSULTAS_H
