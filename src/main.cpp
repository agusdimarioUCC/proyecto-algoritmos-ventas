#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "hashMapList.h"
#include "lista.h"
#include "procesador_de_csv.h"
#include "venta.h"
using namespace std;

unordered_map<string, vector<Venta>> hashPorID;
vector<Venta> ventas;
HashMapList<int, Venta> mapaVentas;
// Estructura auxiliar para ordenar
struct CiudadMonto
{
    string ciudad;
    double monto;

    CiudadMonto(const string& c, double m): ciudad(c), monto(m)
    {
    }
};

struct ProductoMonto
{
    string producto;
    double monto;

    ProductoMonto(const string& p, double m): producto(p), monto(m)
    {
    }
};

struct CategoriaProm
{
    string categoria;
    double prom;

    CategoriaProm(const string& c, double p): categoria(c), prom(p)
    {
    }
};

struct MedioCont
{
    string medio;
    int cont;

    MedioCont(const string& m, int c): medio(m), cont(c)
    {
    }
};

struct EstadoCont
{
    string estado;
    int cont;

    EstadoCont(const string& e, int c): estado(e), cont(c)
    {
    }
};

struct DiaMonto
{
    string dia;
    double monto;

    DiaMonto(const string& d, double m): dia(d), monto(m)
    {
    }
};

struct ProductoCant
{
    string producto;
    int cant;

    ProductoCant(const string& p, int c): producto(p), cant(c)
    {
    }
};

// 1. Top 5 ciudades con mayor monto de ventas por país
void top5CiudadesPorPais(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, HashMapList<string, double>> paisCiudadMontos;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, double> ciudades;
            try { ciudades = paisCiudadMontos.get(v.pais); }
            catch (...)
            {
            }
            double monto = 0;
            try { monto = ciudades.get(v.ciudad); }
            catch (...)
            {
            }
            ciudades.put(v.ciudad, monto + v.montoTotal);
            paisCiudadMontos.put(v.pais, ciudades);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisCiudadMontos.getcapacidad(); ++i)
    {
        auto* bucket = paisCiudadMontos.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string pais = nodo->getDato().getClave();
            HashMapList<string, double> ciudades = nodo->getDato().getValor();
            Lista<CiudadMonto> listaCiudades;
            for (int j = 0; j < ciudades.getcapacidad(); ++j)
            {
                auto* b2 = ciudades.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2)
                {
                    string ciudad = n2->getDato().getClave();
                    double monto = n2->getDato().getValor();
                    listaCiudades.insertarUltimo(CiudadMonto(ciudad, monto));
                    n2 = n2->getSiguiente();
                }
            }
            std::vector<CiudadMonto> vec;
            for (int k = 0; k < listaCiudades.getTamanio(); ++k)
                vec.push_back(listaCiudades.getDato(k));
            std::sort(vec.begin(), vec.end(), [](const CiudadMonto& a, const CiudadMonto& b)
            {
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

// 2. Monto total vendido por producto, discriminado por país
void montoPorProductoPorPais(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, HashMapList<string, double>> paisProductoMontos;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, double> productos;
            try { productos = paisProductoMontos.get(v.pais); }
            catch (...)
            {
            }
            double monto = 0;
            try { monto = productos.get(v.producto); }
            catch (...)
            {
            }
            productos.put(v.producto, monto + v.montoTotal);
            paisProductoMontos.put(v.pais, productos);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisProductoMontos.getcapacidad(); ++i)
    {
        auto* bucket = paisProductoMontos.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string pais = nodo->getDato().getClave();
            HashMapList<string, double> productos = nodo->getDato().getValor();
            cout << "Pais: " << pais << endl;
            for (int j = 0; j < productos.getcapacidad(); ++j)
            {
                auto* b2 = productos.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2)
                {
                    cout << "  Producto: " << n2->getDato().getClave() << " - $" << n2->getDato().getValor() << endl;
                    n2 = n2->getSiguiente();
                }
            }
            cout << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// 3. Promedio de ventas por categoría en cada país
void promedioPorCategoriaPorPais(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, HashMapList<string, double>> paisCategoriaMontos;
    HashMapList<string, HashMapList<string, int>> paisCategoriaCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, double> catMontos;
            HashMapList<string, int> catCont;
            try { catMontos = paisCategoriaMontos.get(v.pais); }
            catch (...)
            {
            }
            try { catCont = paisCategoriaCont.get(v.pais); }
            catch (...)
            {
            }
            double monto = 0;
            int cont = 0;
            try { monto = catMontos.get(v.categoria); }
            catch (...)
            {
            }
            try { cont = catCont.get(v.categoria); }
            catch (...)
            {
            }
            catMontos.put(v.categoria, monto + v.montoTotal);
            catCont.put(v.categoria, cont + 1);
            paisCategoriaMontos.put(v.pais, catMontos);
            paisCategoriaCont.put(v.pais, catCont);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisCategoriaMontos.getcapacidad(); ++i)
    {
        auto* bucket = paisCategoriaMontos.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string pais = nodo->getDato().getClave();
            HashMapList<string, double> catMontos = nodo->getDato().getValor();
            HashMapList<string, int> catCont = paisCategoriaCont.get(pais);
            cout << "Pais: " << pais << endl;
            for (int j = 0; j < catMontos.getcapacidad(); ++j)
            {
                auto* b2 = catMontos.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2)
                {
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

// 4. Medio de envío más utilizado por país
void medioEnvioMasUsadoPorPais(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, HashMapList<string, int>> paisMedioCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, int> medios;
            try { medios = paisMedioCont.get(v.pais); }
            catch (...)
            {
            }
            int cont = 0;
            try { cont = medios.get(v.medioEnvio); }
            catch (...)
            {
            }
            medios.put(v.medioEnvio, cont + 1);
            paisMedioCont.put(v.pais, medios);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisMedioCont.getcapacidad(); ++i)
    {
        auto* bucket = paisMedioCont.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string pais = nodo->getDato().getClave();
            HashMapList<string, int> medios = nodo->getDato().getValor();
            string maxMedio;
            int maxCont = 0;
            for (int j = 0; j < medios.getcapacidad(); ++j)
            {
                auto* b2 = medios.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2)
                {
                    string medio = n2->getDato().getClave();
                    int cont = n2->getDato().getValor();
                    if (cont > maxCont)
                    {
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

// 5. Medio de envío más utilizado por categoría
void medioEnvioMasUsadoPorCategoria(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, HashMapList<string, int>> catMedioCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, int> medios;
            try { medios = catMedioCont.get(v.categoria); }
            catch (...)
            {
            }
            int cont = 0;
            try { cont = medios.get(v.medioEnvio); }
            catch (...)
            {
            }
            medios.put(v.medioEnvio, cont + 1);
            catMedioCont.put(v.categoria, medios);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < catMedioCont.getcapacidad(); ++i)
    {
        auto* bucket = catMedioCont.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string cat = nodo->getDato().getClave();
            HashMapList<string, int> medios = nodo->getDato().getValor();
            string maxMedio;
            int maxCont = 0;
            for (int j = 0; j < medios.getcapacidad(); ++j)
            {
                auto* b2 = medios.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2)
                {
                    string medio = n2->getDato().getClave();
                    int cont = n2->getDato().getValor();
                    if (cont > maxCont)
                    {
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

// 6. Día con mayor cantidad de ventas (por monto de dinero) en toda la base de datos
void diaMayorMonto(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, double> diaMonto;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            double monto = 0;
            try { monto = diaMonto.get(v.fecha); }
            catch (...)
            {
            }
            diaMonto.put(v.fecha, monto + v.montoTotal);
            nodo = nodo->getSiguiente();
        }
    }
    string maxDia;
    double maxMonto = 0;
    for (int i = 0; i < diaMonto.getcapacidad(); ++i)
    {
        auto* bucket = diaMonto.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string dia = nodo->getDato().getClave();
            double monto = nodo->getDato().getValor();
            if (monto > maxMonto)
            {
                maxMonto = monto;
                maxDia = dia;
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Dia con mayor monto de ventas: " << maxDia << " ($" << maxMonto << ")" << endl;
}

// 7. Estado de envío más frecuente por país
void estadoEnvioMasFrecuentePorPais(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, HashMapList<string, int>> paisEstadoCont;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            HashMapList<string, int> estados;
            try { estados = paisEstadoCont.get(v.pais); }
            catch (...)
            {
            }
            int cont = 0;
            try { cont = estados.get(v.estadoEnvio); }
            catch (...)
            {
            }
            estados.put(v.estadoEnvio, cont + 1);
            paisEstadoCont.put(v.pais, estados);
            nodo = nodo->getSiguiente();
        }
    }
    for (int i = 0; i < paisEstadoCont.getcapacidad(); ++i)
    {
        auto* bucket = paisEstadoCont.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string pais = nodo->getDato().getClave();
            HashMapList<string, int> estados = nodo->getDato().getValor();
            string maxEstado;
            int maxCont = 0;
            for (int j = 0; j < estados.getcapacidad(); ++j)
            {
                auto* b2 = estados.getBuckets()[j];
                if (!b2) continue;
                auto* n2 = b2->getInicio();
                while (n2)
                {
                    string estado = n2->getDato().getClave();
                    int cont = n2->getDato().getValor();
                    if (cont > maxCont)
                    {
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
void productoMasVendido(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, int> productoCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            int cant = 0;
            try { cant = productoCant.get(v.producto); }
            catch (...)
            {
            }
            productoCant.put(v.producto, cant + v.cantidad);
            nodo = nodo->getSiguiente();
        }
    }
    string maxProd;
    int maxCant = 0;
    for (int i = 0; i < productoCant.getcapacidad(); ++i)
    {
        auto* bucket = productoCant.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string prod = nodo->getDato().getClave();
            int cant = nodo->getDato().getValor();
            if (cant > maxCant)
            {
                maxCant = cant;
                maxProd = prod;
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Producto mas vendido (en unidades): " << maxProd << " (" << maxCant << " unidades)" << endl;
}

// 9. Producto menos vendido en cantidad total (unidades)
void productoMenosVendido(HashMapList<int, Venta>& mapaVentas)
{
    HashMapList<string, int> productoCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            int cant = 0;
            try { cant = productoCant.get(v.producto); }
            catch (...)
            {
            }
            productoCant.put(v.producto, cant + v.cantidad);
            nodo = nodo->getSiguiente();
        }
    }
    string minProd;
    int minCant = INT_MAX;
    for (int i = 0; i < productoCant.getcapacidad(); ++i)
    {
        auto* bucket = productoCant.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string prod = nodo->getDato().getClave();
            int cant = nodo->getDato().getValor();
            if (cant < minCant)
            {
                minCant = cant;
                minProd = prod;
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Producto menos vendido (en unidades): " << minProd << " (" << minCant << " unidades)" << endl;
}


// Listado de ventas realizadas en una ciudad específica
void ventasPorCiudad(HashMapList<int, Venta>& mapaVentas, const string& ciudad)
{
    cout << "Ventas en la ciudad: " << ciudad << endl;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            if (v.ciudad == ciudad)
            {
                cout << "Producto: " << v.producto << ", Monto: $" << v.montoTotal << ", Fecha: " << v.fecha << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}

// Listado de ventas realizadas en un rango de fechas por país
void ventasPorRangoFechasYPais(HashMapList<int, Venta>& mapaVentas, const string& pais, const string& fechaInicio,
                               const string& fechaFin)
{
    cout << "Ventas en " << pais << " desde " << fechaInicio << " hasta " << fechaFin << ":" << endl;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            if (v.pais == pais && v.fecha >= fechaInicio && v.fecha <= fechaFin)
            {
                cout << "Fecha: " << v.fecha << ", Producto: " << v.producto << ", Monto: $" << v.montoTotal << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}

// Comparación entre dos países: monto total, productos más vendidos, medio de envío más usado
void compararPaises(HashMapList<int, Venta>& mapaVentas, const string& pais1, const string& pais2)
{
    double monto1 = 0, monto2 = 0;
    HashMapList<string, int> prod1, prod2;
    HashMapList<string, int> envio1, envio2;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            if (v.pais == pais1)
            {
                monto1 += v.montoTotal;
                int c = 0;
                try { c = prod1.get(v.producto); }
                catch (...)
                {
                }
                prod1.put(v.producto, c + v.cantidad);
                int e = 0;
                try { e = envio1.get(v.medioEnvio); }
                catch (...)
                {
                }
                envio1.put(v.medioEnvio, e + 1);
            }
            if (v.pais == pais2)
            {
                monto2 += v.montoTotal;
                int c = 0;
                try { c = prod2.get(v.producto); }
                catch (...)
                {
                }
                prod2.put(v.producto, c + v.cantidad);
                int e = 0;
                try { e = envio2.get(v.medioEnvio); }
                catch (...)
                {
                }
                envio2.put(v.medioEnvio, e + 1);
            }
            nodo = nodo->getSiguiente();
        }
    }
    // Producto más vendido y medio de envío más usado
    auto maxKey = [](HashMapList<string, int>& map)
    {
        string key;
        int max = 0;
        for (int i = 0; i < map.getcapacidad(); ++i)
        {
            auto* bucket = map.getBuckets()[i];
            if (!bucket) continue;
            auto* nodo = bucket->getInicio();
            while (nodo)
            {
                if (nodo->getDato().getValor() > max)
                {
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
void compararProductos(HashMapList<int, Venta>& mapaVentas, const string& prod1, const string& prod2)
{
    HashMapList<string, int> cant1, cant2;
    HashMapList<string, double> monto1, monto2;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            if (v.producto == prod1)
            {
                int c = 0;
                try { c = cant1.get(v.pais); }
                catch (...)
                {
                }
                double m = 0;
                try { m = monto1.get(v.pais); }
                catch (...)
                {
                }
                cant1.put(v.pais, c + v.cantidad);
                monto1.put(v.pais, m + v.montoTotal);
            }
            if (v.producto == prod2)
            {
                int c = 0;
                try { c = cant2.get(v.pais); }
                catch (...)
                {
                }
                double m = 0;
                try { m = monto2.get(v.pais); }
                catch (...)
                {
                }
                cant2.put(v.pais, c + v.cantidad);
                monto2.put(v.pais, m + v.montoTotal);
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Comparacion entre productos '" << prod1 << "' y '" << prod2 << "':\n";
    cout << "Pais\t" << prod1 << " (cant)\t" << prod1 << " ($)\t" << prod2 << " (cant)\t" << prod2 << " ($)\n";
    for (int i = 0; i < cant1.getcapacidad(); ++i)
    {
        auto* bucket = cant1.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string pais = nodo->getDato().getClave();
            int c1 = nodo->getDato().getValor();
            double m1 = 0;
            try { m1 = monto1.get(pais); }
            catch (...)
            {
            }
            int c2 = 0;
            try { c2 = cant2.get(pais); }
            catch (...)
            {
            }
            double m2 = 0;
            try { m2 = monto2.get(pais); }
            catch (...)
            {
            }
            cout << pais << "\t" << c1 << "\t\t$" << m1 << "\t" << c2 << "\t\t$" << m2 << endl;
            nodo = nodo->getSiguiente();
        }
    }
}

// Buscar productos vendidos en promedio por debajo de un monto total especificado por el usuario y por país
void productosPromedioPorDebajo(HashMapList<int, Venta>& mapaVentas, const string& pais, double umbral)
{
    HashMapList<string, double> prodMonto;
    HashMapList<string, int> prodCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            if (v.pais == pais)
            {
                double m = 0;
                int c = 0;
                try { m = prodMonto.get(v.producto); }
                catch (...)
                {
                }
                try { c = prodCant.get(v.producto); }
                catch (...)
                {
                }
                prodMonto.put(v.producto, m + v.montoTotal);
                prodCant.put(v.producto, c + v.cantidad);
            }
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Productos con monto promedio por unidad menor a $" << umbral << " en " << pais << ":\n";
    for (int i = 0; i < prodMonto.getcapacidad(); ++i)
    {
        auto* bucket = prodMonto.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string prod = nodo->getDato().getClave();
            double monto = nodo->getDato().getValor();
            int cant = 0;
            try { cant = prodCant.get(prod); }
            catch (...)
            {
            }
            if (cant > 0 && (monto / cant) < umbral)
            {
                cout << prod << " (promedio: $" << (monto / cant) << ")" << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}

// Buscar productos vendidos en promedio por encima de un monto total especificado por el usuario
void productosPromedioPorEncima(HashMapList<int, Venta>& mapaVentas, double umbral)
{
    HashMapList<string, double> prodMonto;
    HashMapList<string, int> prodCant;
    for (int i = 0; i < mapaVentas.getcapacidad(); ++i)
    {
        auto* bucket = mapaVentas.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            const Venta& v = nodo->getDato().getValor();
            double m = 0;
            int c = 0;
            try { m = prodMonto.get(v.producto); }
            catch (...)
            {
            }
            try { c = prodCant.get(v.producto); }
            catch (...)
            {
            }
            prodMonto.put(v.producto, m + v.montoTotal);
            prodCant.put(v.producto, c + v.cantidad);
            nodo = nodo->getSiguiente();
        }
    }
    cout << "Productos con monto promedio por unidad mayor a $" << umbral << ":\n";
    for (int i = 0; i < prodMonto.getcapacidad(); ++i)
    {
        auto* bucket = prodMonto.getBuckets()[i];
        if (!bucket) continue;
        auto* nodo = bucket->getInicio();
        while (nodo)
        {
            string prod = nodo->getDato().getClave();
            double monto = nodo->getDato().getValor();
            int cant = 0;
            try { cant = prodCant.get(prod); }
            catch (...)
            {
            }
            if (cant > 0 && (monto / cant) > umbral)
            {
                cout << prod << " (promedio: $" << (monto / cant) << ")" << endl;
            }
            nodo = nodo->getSiguiente();
        }
    }
}

// --------------------- CONSTRUIR HASH ---------------------

void construirHash() {
    mapaVentas.clear();
    for (int i=0, n=ventas.size(); i<n; ++i)
    {
        const Venta& v = ventas[i];
        mapaVentas.put(v.idVenta, v);
    }
}

// --------------------- AGREGAR VENTA ---------------------

void agregarVenta() {
    Venta nueva;
    string entrada;

    cout << "Ingrese los datos de la nueva venta:\n";

    try {
        cout << "ID: ";
        std::cin >> nueva.idVenta;

        do {
            cout << "Fecha (YYYY-MM-DD): ";
            getline(cin >> ws, nueva.fecha);
            if (!nueva.fecha.empty()) break;
            cout << "La fecha no puede estar vacía.\n";
        } while (nueva.fecha.empty());

        do {
            cout << "País: ";
            getline(cin >> ws, nueva.pais);
            if (!nueva.pais.empty()) break;
            cout << "El país no puede estar vacío.\n";
        } while (nueva.pais.empty());

        do {
            cout << "Ciudad: ";
            getline(cin >> ws, nueva.ciudad);
            if (!nueva.ciudad.empty()) break;
            cout << "La ciudad no puede estar vacía.\n";
        } while (nueva.ciudad.empty());

        do {
            cout << "Cliente: ";
            getline(cin >> ws, nueva.cliente);
            if (!nueva.cliente.empty()) break;
            cout << "El cliente no puede estar vacío.\n";
        } while (nueva.cliente.empty());

        do {
            cout << "Producto: ";
            getline(cin >> ws, nueva.producto);
            if (!nueva.producto.empty()) break;
            cout << "El producto no puede estar vacío.\n";
        } while (nueva.producto.empty());

        do {
            cout << "Categoría: ";
            getline(cin >> ws, nueva.categoria);
            if (!nueva.categoria.empty()) break;
            cout << "La categoría no puede estar vacía.\n";
        } while (nueva.categoria.empty());

        bool cantidadValida = false;
        do {
            cout << "Cantidad: ";
            getline(cin >> ws, entrada);
            try {
                nueva.cantidad = stoi(entrada);
                if (nueva.cantidad > 0) {
                    cantidadValida = true;
                } else {
                    cout << "La cantidad debe ser un número mayor a 0.\n";
                }
            } catch (const invalid_argument&) {
                cout << "Ingrese un número entero válido.\n";
            } catch (const out_of_range&) {
                cout << "Número demasiado grande.\n";
            }
        } while (!cantidadValida);

        bool precioValido = false;
        do {
            cout << "Precio Unitario: ";
            getline(cin >> ws, entrada);
            try {
                nueva.precioUnitario = stof(entrada);
                if (nueva.precioUnitario > 0) {
                    precioValido = true;
                } else {
                    cout << "El precio debe ser mayor a 0.\n";
                }
            } catch (const invalid_argument&) {
                cout << "Ingrese un número decimal válido.\n";
            } catch (const out_of_range&) {
                cout << "Número demasiado grande.\n";
            }
        } while (!precioValido);

        nueva.montoTotal = nueva.cantidad * nueva.precioUnitario;

        do {
            cout << "Medio de Envío: ";
            getline(cin >> ws, nueva.medioEnvio);
            if (!nueva.medioEnvio.empty()) break;
            cout << "El medio de envío no puede estar vacío.\n";
        } while (nueva.medioEnvio.empty());

        do {
            cout << "Estado de Envío: ";
            getline(cin >> ws, nueva.estadoEnvio);
            if (!nueva.estadoEnvio.empty()) break;
            cout << "El estado de envío no puede estar vacío.\n";
        } while (nueva.estadoEnvio.empty());

        ventas.push_back(nueva);
        construirHash();

        cout << "\n>> Venta agregada con éxito.\n";
        cout << ">> Procesando estadísticas nuevamente...\n";

    } catch (const exception& e) {
        cout << "Ocurrió un error inesperado al ingresar la venta: " << e.what() << "\n";
    }
}

// --------------------- ELIMINAR VENTA ---------------------

void eliminarVenta() {
    string filtro;

    do {
        cout << "Ingrese el país o ciudad de la venta a eliminar: ";
        getline(cin >> ws, filtro);
        if (!filtro.empty()) break;
        cout << "El valor ingresado no puede estar vacío.\n";
    } while (filtro.empty());

    try {
        auto it = remove_if(ventas.begin(), ventas.end(), [&](Venta& v) {
            return v.pais == filtro || v.ciudad == filtro;
        });

        if (it != ventas.end()) {
            ventas.erase(it, ventas.end());
            construirHash();
            cout << "\nVentas eliminadas con éxito.\n";
            cout << ">> Reprocesando estadísticas...\n";
        } else {
            cout << "\nNo se encontraron ventas con ese país o ciudad.\n";
        }

    } catch (const exception& e) {
        cerr << "\nOcurrió un error inesperado al intentar eliminar ventas: " << e.what() << endl;
    }
}

// --------------------- MODIFICAR VENTA ---------------------

void modificarVenta() {
    int id;

    cout << "Ingrese el ID de la venta a modificar: ";
    std::cin >> id;

    auto it = find_if(ventas.begin(), ventas.end(), [&](Venta& v) {
        return v.idVenta == id;
    });

    if (it != ventas.end()) {
        cout << "\n--- Modificando Venta ID: " << it->idVenta << " ---\n";

        string entrada;

        do {
            cout << "Nuevo producto: ";
            getline(cin >> ws, it->producto);
            if (!it->producto.empty()) break;
            cout << "El producto no puede estar vacío.\n";
        } while (it->producto.empty());

        bool cantidadValida = false;
        do {
            cout << "Nueva cantidad: ";
            getline(cin >> ws, entrada);
            try {
                it->cantidad = stoi(entrada);
                if (it->cantidad > 0) {
                    cantidadValida = true;
                } else {
                    cout << "La cantidad debe ser mayor a 0.\n";
                }
            } catch (invalid_argument&) {
                cout << "Ingrese un número entero válido.\n";
            } catch (out_of_range&) {
                cout << "El número ingresado es demasiado grande.\n";
            }
        } while (!cantidadValida);

        bool precioValido = false;
        do {
            cout << "Nuevo precio unitario: ";
            getline(cin >> ws, entrada);
            try {
                it->precioUnitario = stof(entrada);
                if (it->precioUnitario > 0) {
                    precioValido = true;
                } else {
                    cout << "El precio debe ser mayor a 0.\n";
                }
            } catch (invalid_argument&) {
                cout << "Ingrese un número decimal válido.\n";
            } catch (out_of_range&) {
                cout << "El número ingresado es demasiado grande.\n";
            }
        } while (!precioValido);

        it->montoTotal = it->cantidad * it->precioUnitario;

        construirHash();

        cout << "\nVenta modificada con éxito.\n";
        cout << ">> Reprocesando estadísticas...\n";

    } else {
        cout << "\nNo se encontró una venta con ese ID.\n";
    }
}


void menu() {
    int opcion;
    do {
        cout << "\n--- MENÚ DE MODIFICACIÓN ---\n";
        cout << "1. Agregar venta\n";
        cout << "2. Eliminar venta\n";
        cout << "3. Modificar venta\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: agregarVenta(); break;
        case 2: eliminarVenta(); break;
        case 3: modificarVenta(); break;
        case 4: cout << "Saliendo...\n"; break;
        default: cout << "Opción inválida.\n";
        }
    } while (opcion != 4);
}


int main()
{
    procesarArchivoCSV("../data/ventas_sudamerica.csv");
menu();
    return 0;
}
