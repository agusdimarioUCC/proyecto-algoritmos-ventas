#include "Consultas.h"
#include <iostream>

void mostrarVentasPorPais(const std::string& pais, HashMapList<std::string, Venta>& ventasPorPais) {
	try {
		ventasPorPais.getList(pais);
	} catch (...) {
		std::cout << "No hay ventas registradas para ese país." << std::endl;
	}
}
