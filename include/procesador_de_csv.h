#ifndef PROCESADOR_CSV_H
#define PROCESADOR_CSV_H
#include <string>
#include "lista.h"
#include "hashMapList.h"

struct Venta;
void procesarArchivoCSV(const std::string& archivo);

// CRUD
void listarTodas();
void buscarPorID();
void agregarVenta();
void modificarVenta();
void eliminarPorPaisOCiudad();

void analisisVentas(); // opción 6
void recalcularEstadisticas(); // llamada interna

#endif
