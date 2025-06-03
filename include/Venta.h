#ifndef VENTA_H
#define VENTA_H

#include <string>
using namespace std;

struct Venta {
    string idVenta;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    float precioUnitario;
    float montoTotal;         // cantidad * precioUnitario, puede validarse
    string medioEnvio;
    string estadoEnvio;

    Venta() {}

    Venta(string id, string f, string p, string c, string cli, string prod, string cat,
          int cant, float precio, float total, string medio, string estado) {
        idVenta = id;
        fecha = f;
        pais = p;
        ciudad = c;
        cliente = cli;
        producto = prod;
        categoria = cat;
        cantidad = cant;
        precioUnitario = precio;
        montoTotal = total;
        medioEnvio = medio;
        estadoEnvio = estado;
    }
};

#endif // VENTA_H
