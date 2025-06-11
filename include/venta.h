#ifndef VENTA_H
#define VENTA_H

#include <string>
using namespace std;

struct Venta
{
    int idVenta;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    double precioUnitario;
    double montoTotal;
    string medioEnvio;
    string estadoEnvio;
};

#endif
