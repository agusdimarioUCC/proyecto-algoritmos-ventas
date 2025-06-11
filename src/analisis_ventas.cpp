#include <algorithm>
#include <iostream>
#include <vector>
#include "analisis_ventas.h"
#include "estructuras_analisis.h"
#include "lista.h"
using namespace std;

// 1. Top 5 ciudades con mayor monto de ventas por pais
void top5CiudadesPorPais(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, HashMapList<string, double>> paisCiudadMontos;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, double> ciudades;
            try { ciudades = paisCiudadMontos.get(v.pais); }
            catch (...) {}
            double monto = 0;
            try { monto = ciudades.get(v.ciudad); }
            catch (...) {}
            ciudades.put(v.ciudad, monto + v.montoTotal);
            paisCiudadMontos.put(v.pais, ciudades);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisCiudadMontos.getcapacidad(); ++i) {
        auto* bucket = paisCiudadMontos.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string pais = nodo->getDato().getClave();
            HashMapList<string, double> ciudades = nodo->getDato().getValor();
            Lista<CiudadMonto> listaCiudades;
            for (int j = 0; j < ciudades.getcapacidad(); ++j) {
                auto* b2 = ciudades.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2) {
                    string ciudad = n2->getDato().getClave();
                    double monto = n2->getDato().getValor();
                    listaCiudades.insertarUltimo(CiudadMonto(ciudad, monto));
                    n2 = n2->getSiguiente();
                }
            }
            std::vector<CiudadMonto> vec;
            for (int k = 0; k < listaCiudades.getTamanio(); ++k)
                vec.push_back(listaCiudades.getDato(k));
            std::sort(vec.begin(), vec.end(), [](const CiudadMonto& a, const CiudadMonto& b) {
                return a.monto > b.monto;
            });
            cout << "Top 5 ciudades con mayor monto de ventas en " << pais << ":\n";
            for (int k = 0; k < 5 && k < static_cast<int>(vec.size()); ++k)
                cout << "  " << vec[k].ciudad << ": $" << vec[k].monto << endl;
            cout << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// 2. Monto total vendido por producto, discriminado por pais
void montoPorProductoPorPais(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, HashMapList<string, double>> paisProductoMontos;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, double> productos;
            try { productos = paisProductoMontos.get(v.pais); }
            catch (...) {}
            double monto = 0;
            try { monto = productos.get(v.producto); }
            catch (...) {}
            productos.put(v.producto, monto + v.montoTotal);
            paisProductoMontos.put(v.pais, productos);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisProductoMontos.getcapacidad(); ++i) {
        auto* bucket = paisProductoMontos.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string pais = nodo->getDato().getClave();
            HashMapList<string, double> productos = nodo->getDato().getValor();
            cout << "Pais: " << pais << endl;
            for (int j = 0; j < productos.getcapacidad(); ++j) {
                auto* b2 = productos.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2) {
                    cout << "  Producto: " << n2->getDato().getClave() << " - $" << n2->getDato().getValor() << endl;
                    n2 = n2->getSiguiente();
                }
            }
            cout << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// 3. Promedio de ventas por categoria en cada pais
void promedioPorCategoriaPorPais(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, HashMapList<string, double>> paisCategoriaMontos;
    HashMapList<string, HashMapList<string, int>> paisCategoriaCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, double> catMontos;
            HashMapList<string, int> catCont;
            try { catMontos = paisCategoriaMontos.get(v.pais); }
            catch (...) {}
            try { catCont = paisCategoriaCont.get(v.pais); }
            catch (...) {}
            double monto = 0;
            int cont = 0;
            try { monto = catMontos.get(v.categoria); }
            catch (...) {}
            try { cont = catCont.get(v.categoria); }
            catch (...) {}
            catMontos.put(v.categoria, monto + v.montoTotal);
            catCont.put(v.categoria, cont + 1);
            paisCategoriaMontos.put(v.pais, catMontos);
            paisCategoriaCont.put(v.pais, catCont);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisCategoriaMontos.getcapacidad(); ++i) {
        auto* bucket = paisCategoriaMontos.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string pais = nodo->getDato().getClave();
            HashMapList<string, double> catMontos = nodo->getDato().getValor();
            HashMapList<string, int> catCont = paisCategoriaCont.get(pais);
            cout << "Pais: " << pais << endl;
            for (int j = 0; j < catMontos.getcapacidad(); ++j) {
                auto* b2 = catMontos.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2) {
                    string cat = n2->getDato().getClave();
                    double monto = n2->getDato().getValor();
                    int cont = catCont.get(cat);
                    cout << "  Categoria: " << cat << " - Promedio: $" << (monto / cont) << endl;
                    n2 = n2->getSiguiente();
                }
            }
            cout << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// 4. Medio de envio más utilizado por pais
void medioEnvioMasUsadoPorPais(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, HashMapList<string, int>> paisMedioCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, int> medios;
            try { medios = paisMedioCont.get(v.pais); }
            catch (...) {}
            int cont = 0;
            try { cont = medios.get(v.medioEnvio); }
            catch (...) {}
            medios.put(v.medioEnvio, cont + 1);
            paisMedioCont.put(v.pais, medios);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisMedioCont.getcapacidad(); ++i) {
        auto* bucket = paisMedioCont.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string pais = nodo->getDato().getClave();
            HashMapList<string, int> medios = nodo->getDato().getValor();
            string maxMedio;
            int maxCont = 0;
            for (int j = 0; j < medios.getcapacidad(); ++j) {
                auto* b2 = medios.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2) {
                    string medio = n2->getDato().getClave();
                    int cont = n2->getDato().getValor();
                    if (cont > maxCont) {
                        maxCont = cont;
                        maxMedio = medio;
                    }
                    n2 = n2->getSiguiente();
                }
            }
            cout << "Pais: " << pais << " - Medio de envio mas usado: " << maxMedio << " (" << maxCont << " veces)" <<
                endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// 5. Medio de envio más utilizado por categoria
void medioEnvioMasUsadoPorCategoria(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, HashMapList<string, int>> catMedioCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, int> medios;
            try { medios = catMedioCont.get(v.categoria); }
            catch (...) {}
            int cont = 0;
            try { cont = medios.get(v.medioEnvio); }
            catch (...) {}
            medios.put(v.medioEnvio, cont + 1);
            catMedioCont.put(v.categoria, medios);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < catMedioCont.getcapacidad(); ++i) {
        auto* bucket = catMedioCont.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string cat = nodo->getDato().getClave();
            HashMapList<string, int> medios = nodo->getDato().getValor();
            string maxMedio;
            int maxCont = 0;
            for (int j = 0; j < medios.getcapacidad(); ++j) {
                auto* b2 = medios.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2) {
                    string medio = n2->getDato().getClave();
                    int cont = n2->getDato().getValor();
                    if (cont > maxCont) {
                        maxCont = cont;
                        maxMedio = medio;
                    }
                    n2 = n2->getSiguiente();
                }
            }
            cout << "Categoria: " << cat << " - Medio de envio mas usado: " << maxMedio << " (" << maxCont << " veces)"
                << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// 6. Dia con mayor cantidad de ventas (por monto de dinero) en toda la base de datos
void diaMayorMonto(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, double> diaMonto;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            double monto = 0;
            try { monto = diaMonto.get(v.fecha); }
            catch (...) {}
            diaMonto.put(v.fecha, monto + v.montoTotal);
            nodo = nodo->getSiguiente();
        }
    }
    string maxDia;
    double maxMonto = 0;
    for (int i = 0; i < diaMonto.getcapacidad(); ++i) {
        auto* bucket = diaMonto.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string dia = nodo->getDato().getClave();
            double monto = nodo->getDato().getValor();
            if (monto > maxMonto) {
                maxMonto = monto;
                maxDia = dia;
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Dia con mayor monto de ventas: " << maxDia << " ($" << maxMonto << ")" << endl;
}

// 7. Estado de envio más frecuente por pais
void estadoEnvioMasFrecuentePorPais(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, HashMapList<string, int>> paisEstadoCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, int> estados;
            try { estados = paisEstadoCont.get(v.pais); }
            catch (...) {}
            int cont = 0;
            try { cont = estados.get(v.estadoEnvio); }
            catch (...) {}
            estados.put(v.estadoEnvio, cont + 1);
            paisEstadoCont.put(v.pais, estados);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisEstadoCont.getcapacidad(); ++i) {
        auto* bucket = paisEstadoCont.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string pais = nodo->getDato().getClave();
            HashMapList<string, int> estados = nodo->getDato().getValor();
            string maxEstado;
            int maxCont = 0;
            for (int j = 0; j < estados.getcapacidad(); ++j) {
                auto* b2 = estados.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2) {
                    string estado = n2->getDato().getClave();
                    int cont = n2->getDato().getValor();
                    if (cont > maxCont) {
                        maxCont = cont;
                        maxEstado = estado;
                    }
                    n2 = n2->getSiguiente();
                }
            }
            cout << "Pais: " << pais << " - Estado de envio mas frecuente: " << maxEstado << " (" << maxCont <<
                " veces)" << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// 8. Producto más vendido en cantidad total (unidades)
void productoMasVendido(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, int> productoCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            int cant = 0;
            try { cant = productoCant.get(v.producto); }
            catch (...) {}
            productoCant.put(v.producto, cant + v.cantidad);
            nodo = nodo->getSiguiente();
        }
    }
    string maxProd;
    int maxCant = 0;
    for (int i = 0; i < productoCant.getcapacidad(); ++i) {
        auto* bucket = productoCant.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string prod = nodo->getDato().getClave();
            int cant = nodo->getDato().getValor();
            if (cant > maxCant) {
                maxCant = cant;
                maxProd = prod;
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Producto mas vendido (en unidades): " << maxProd << " (" << maxCant << " unidades)" << endl;
}

// 9. Producto menos vendido en cantidad total (unidades)
void productoMenosVendido(HashMapList<int, Venta>& mapaVentas) {
    HashMapList<string, int> productoCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            int cant = 0;
            try { cant = productoCant.get(v.producto); }
            catch (...) {}
            productoCant.put(v.producto, cant + v.cantidad);
            nodo = nodo->getSiguiente();
        }
    }
    string minProd;
    int minCant = INT_MAX;
    for (int i = 0; i < productoCant.getcapacidad(); ++i) {
        auto* bucket = productoCant.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string prod = nodo->getDato().getClave();
            int cant = nodo->getDato().getValor();
            if (cant < minCant) {
                minCant = cant;
                minProd = prod;
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Producto menos vendido (en unidades): " << minProd << " (" << minCant << " unidades)" << endl;
}

// Listado de ventas realizadas en una ciudad especifica
void ventasPorCiudad(HashMapList<int, Venta>& mapaVentas, const string& ciudad) {
    cout << "Ventas en la ciudad: " << ciudad << endl;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            if (v.ciudad == ciudad) {
                cout << "Producto: " << v.producto << ", Monto: $" << v.montoTotal << ", Fecha: " << v.fecha << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}

// Listado de ventas realizadas en un rango de fechas por país
void ventasPorRangoFechasYPais(HashMapList<int, Venta>& mapaVentas, const string& pais, const string& fechaInicio,
                              const string& fechaFin) {
    cout << "Ventas en " << pais << " desde " << fechaInicio << " hasta " << fechaFin << ":" << endl;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            if (v.pais == pais && v.fecha >= fechaInicio && v.fecha <= fechaFin) {
                cout << "Fecha: " << v.fecha << ", Producto: " << v.producto << ", Monto: $" << v.montoTotal << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}

// Comparación entre dos países: monto total, productos más vendidos, medio de envío más usado
void compararPaises(HashMapList<int, Venta>& mapaVentas, const string& pais1, const string& pais2) {
    double monto1 = 0, monto2 = 0;
    HashMapList<string, int> prod1, prod2;
    HashMapList<string, int> envio1, envio2;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            if (v.pais == pais1) {
                monto1 += v.montoTotal;
                int c = 0;
                try { c = prod1.get(v.producto); }
                catch (...) {}
                prod1.put(v.producto, c + v.cantidad);
                int e = 0;
                try { e = envio1.get(v.medioEnvio); }
                catch (...) {}
                envio1.put(v.medioEnvio, e + 1);
            }
            if (v.pais == pais2) {
                monto2 += v.montoTotal;
                int c = 0;
                try { c = prod2.get(v.producto); }
                catch (...) {}
                prod2.put(v.producto, c + v.cantidad);
                int e = 0;
                try { e = envio2.get(v.medioEnvio); }
                catch (...) {}
                envio2.put(v.medioEnvio, e + 1);
            }
            nodo = nodo->getSiguiente();
        }
    }
    // Producto más vendido y medio de envío más usado
    auto maxKey = [](HashMapList<string, int>& map) {
        string key;
        int max = 0;
        for (int i = 0; i < map.getcapacidad(); ++i) {
            auto* bucket = map.getBuckets()[i];
            if (!bucket) continue;
            auto* nodo = bucket->getInicio();
            while (nodo) {
                if (nodo->getDato().getValor() > max) {
                    max = nodo->getDato().getValor();
                    key = nodo->getDato().getClave();
                }
                nodo = nodo->getSiguiente();
            }
        }
        return key;
    };
    cout << "Comparacion entre " << pais1 << " y " << pais2 << ":\n";
    cout << pais1 << " - Monto total: $" << monto1 << ", Producto mas vendido: " << maxKey(prod1) <<
        ", Medio envio mas usado: " << maxKey(envio1) << endl;
    cout << pais2 << " - Monto total: $" << monto2 << ", Producto mas vendido: " << maxKey(prod2) <<
        ", Medio envio mas usado: " << maxKey(envio2) << endl;
}

// Comparación entre dos productos discriminado por todos los países
void compararProductos(HashMapList<int, Venta>& mapaVentas, const string& prod1, const string& prod2) {
    HashMapList<string, int> cant1, cant2;
    HashMapList<string, double> monto1, monto2;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            if (v.producto == prod1) {
                int c = 0;
                try { c = cant1.get(v.pais); }
                catch (...) {}
                double m = 0;
                try { m = monto1.get(v.pais); }
                catch (...) {}
                cant1.put(v.pais, c + v.cantidad);
                monto1.put(v.pais, m + v.montoTotal);
            }
            if (v.producto == prod2) {
                int c = 0;
                try { c = cant2.get(v.pais); }
                catch (...) {}
                double m = 0;
                try { m = monto2.get(v.pais); }
                catch (...) {}
                cant2.put(v.pais, c + v.cantidad);
                monto2.put(v.pais, m + v.montoTotal);
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Comparacion entre productos '" << prod1 << "' y '" << prod2 << "':\n";
    cout << "Pais\t" << prod1 << " (cant)\t" << prod1 << " ($)\t" << prod2 << " (cant)\t" << prod2 << " ($)\n";
    for (int i = 0; i < cant1.getcapacidad(); ++i) {
        auto* bucket = cant1.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string pais = nodo->getDato().getClave();
            int c1 = nodo->getDato().getValor();
            double m1 = 0;
            try { m1 = monto1.get(pais); }
            catch (...) {}
            int c2 = 0;
            try { c2 = cant2.get(pais); }
            catch (...) {}
            double m2 = 0;
            try { m2 = monto2.get(pais); }
            catch (...) {}
            cout << pais << "\t" << c1 << "\t\t$" << m1 << "\t" << c2 << "\t\t$" << m2 << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// Buscar productos vendidos en promedio por debajo de un monto total especificado por el usuario y por país
void productosPromedioPorDebajo(HashMapList<int, Venta>& mapaVentas, const string& pais, double umbral) {
    HashMapList<string, double> prodMonto;
    HashMapList<string, int> prodCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            if (v.pais == pais) {
                double m = 0;
                int c = 0;
                try { m = prodMonto.get(v.producto); }
                catch (...) {}
                try { c = prodCant.get(v.producto); }
                catch (...) {}
                prodMonto.put(v.producto, m + v.montoTotal);
                prodCant.put(v.producto, c + v.cantidad);
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Productos con monto promedio por unidad menor a $" << umbral << " en " << pais << ":\n";
    for (int i = 0; i < prodMonto.getcapacidad(); ++i) {
        auto* bucket = prodMonto.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string prod = nodo->getDato().getClave();
            double monto = nodo->getDato().getValor();
            int cant = 0;
            try { cant = prodCant.get(prod); }
            catch (...) {}
            if (cant > 0 && (monto / cant) < umbral) {
                cout << prod << " (promedio: $" << (monto / cant) << ")" << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}

// Buscar productos vendidos en promedio por encima de un monto total especificado por el usuario
void productosPromedioPorEncima(HashMapList<int, Venta>& mapaVentas, double umbral) {
    HashMapList<string, double> prodMonto;
    HashMapList<string, int> prodCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i) {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            const Venta& v = nodo->getDato().getValor();
            double m = 0;
            int c = 0;
            try { m = prodMonto.get(v.producto); }
            catch (...) {}
            try { c = prodCant.get(v.producto); }
            catch (...) {}
            prodMonto.put(v.producto, m + v.montoTotal);
            prodCant.put(v.producto, c + v.cantidad);
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Productos con monto promedio por unidad mayor a $" << umbral << ":\n";
    for (int i = 0; i < prodMonto.getcapacidad(); ++i) {
        auto* bucket = prodMonto.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo) {
            string prod = nodo->getDato().getClave();
            double monto = nodo->getDato().getValor();
            int cant = 0;
            try { cant = prodCant.get(prod); }
            catch (...) {}
            if (cant > 0 && (monto / cant) > umbral) {
                cout << prod << " (promedio: $" << (monto / cant) << ")" << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}
