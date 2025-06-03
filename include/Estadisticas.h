#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include "EstructurasGlobales.h"
#include "Utilidades.h"

void calcularTopCiudadesPorPais(
    Utilidades &utilidades,
    TopCiudadesPorPais &topCiudadesPorPais
);

void calcularMontoTotalPorProductoPorPais(
    Utilidades &utilidades,
    ProductoPorPais &productoPorPais
);

void calcularPromedioPorCategoriaPorPais(
    Utilidades &utilidades,
    CategoriaPorPais &categoriaPorPais
);

void calcularMedioEnvioMasUsadoPorPais(
    Utilidades &utilidades,
    EnviosPorPais &enviosPorPais
);

void calcularMedioEnvioMasUsadoPorCategoria(
    Utilidades &utilidades,
    EnviosPorCategoria &enviosPorCategoria
);

void calcularDiaConMayorMontoTotal(
    Utilidades &utilidades,
    MapaDiaMonto &diaMonto
);

void calcularEstadoEnvioMasFrecuentePorPais(
    Utilidades &utilidades,
    EstadoPorPais &estadoPorPais
);

void calcularProductoMasYMenosVendidoEnCantidad(
    Utilidades &utilidades,
    MapaProductoCant &productoCantidades
);

#endif // ESTADISTICAS_H
