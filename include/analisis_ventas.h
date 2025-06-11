#ifndef ANALISIS_VENTAS_H
#define ANALISIS_VENTAS_H

#include <string>
#include "hashMapList.h"
#include "venta.h"

// Funciones de análisis de ventas
void top5CiudadesPorPais(HashMapList<int, Venta>& mapaVentas);
void montoPorProductoPorPais(HashMapList<int, Venta>& mapaVentas);
void promedioPorCategoriaPorPais(HashMapList<int, Venta>& mapaVentas);
void medioEnvioMasUsadoPorPais(HashMapList<int, Venta>& mapaVentas);
void medioEnvioMasUsadoPorCategoria(HashMapList<int, Venta>& mapaVentas);
void diaMayorMonto(HashMapList<int, Venta>& mapaVentas);
void estadoEnvioMasFrecuentePorPais(HashMapList<int, Venta>& mapaVentas);
void productoMasVendido(HashMapList<int, Venta>& mapaVentas);
void productoMenosVendido(HashMapList<int, Venta>& mapaVentas);

// Consultas especificas
void ventasPorCiudad(HashMapList<int, Venta>& mapaVentas, const std::string& ciudad);
void ventasPorRangoFechasYPais(HashMapList<int, Venta>& mapaVentas, const std::string& pais, 
                              const std::string& fechaInicio, const std::string& fechaFin);
void compararPaises(HashMapList<int, Venta>& mapaVentas, const std::string& pais1, const std::string& pais2);
void compararProductos(HashMapList<int, Venta>& mapaVentas, const std::string& prod1, const std::string& prod2);
void productosPromedioPorDebajo(HashMapList<int, Venta>& mapaVentas, const std::string& pais, double umbral);
void productosPromedioPorEncima(HashMapList<int, Venta>& mapaVentas, double umbral);

#endif // ANALISIS_VENTAS_H
