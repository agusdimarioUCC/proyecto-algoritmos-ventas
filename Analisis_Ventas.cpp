/*Enunciado General
Crear un programa en C++ que procese el archivo CSV ventas_sudamerica.csv. Este
archivo contiene registros de ventas realizadas por una empresa de logística. El
programa deberá ofrecer, mediante un menú interactivo, funcionalidades que permitan
consultar y analizar los datos de manera dinámica.

Requerimientos del Cliente

1. Eficiencia
Se debe contabilizar el tiempo de ejecución y cantidad de condicionales (if) utilizados
por cada proceso principal. Mostrar al usuario el nombre del proceso, el algoritmo y/o la
estructura utilizada.

2. Librerías
Se permite el uso de las librerías propias de la empresa o cualquier librería estándar. Si
se usan externas, deben ser explicadas y defendidas durante la presentacion.
3. Menú
Debe guiar al usuario con texto contextual y mostrar resultados claros.
Ejemplo (correcto):
La ciudad con mayor monto total de ventas en Perú es Lima, con $35000.


4. Carga de datos desde archivo CSV
El archivo contiene las siguientes columnas:
ID_Venta, Fecha, País, Ciudad, Cliente, Producto, Categoría, Cantidad, Precio_Unitario,
Monto_Total, Medio_Envio, Estado_Envio


5. Procesamiento de datos durante lectura del archivo CSV
Durante la lectura deben calcularse los siguientes resultados principales:
 - El top 5 de ciudades con mayor monto de ventas por país.
- Monto total vendido por producto, discriminado por país.
- Promedio de ventas por categoría en cada país.
 - Medio de envío más utilizado por país - Medio de envío más utilizado por categoría.
- Día con mayor cantidad de ventas (por monto de dinero) en toda la base de datos.
- Estado de envío más frecuente por país.
 - Producto más vendido en cantidad total (no en dinero, sino en unidades).
-  Producto menos vendido en cantidad total.
6. Modificación de datos y reprocesamiento automático
El programa debe permitir: - Agregar una venta (guiando al usuario paso a paso para ingresar todos los campos). - Eliminar una venta (El usuario ingresarà un pais o una ciudad y el programa filtrarà
mostrando lo seleccionado). - Modificar una venta (selección por ID de venta; permitir modificar cualquier campo).
Cada vez que se haga una modificación de datos (agregar, eliminar o modificar), se
deben volver a procesar automáticamente los puntos del apartado 5.

7. Consultas dinámicas solicitadas por el usuario - El listado de ventas realizadas en una ciudad específica. - El listado de ventas realizadas en un rango de fechas por país. - Comparación entre dos países:
a. monto total de ventas
b. productos más vendidos
c. medio de envío más usado.
 - Comparación entre dos productos discriminado por todos los paises:
a. cantidad total vendida
b. monto total - Buscar productos vendidos en promedio por debajo de un monto total especificado por
el usuario (umbral) y por país.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <chrono>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

struct Venta
{
    string ID_Venta;
    string Fecha;
    string Pais;
    string Ciudad;
    string Cliente;
    string Producto;
    string Categoria;
    int Cantidad;
    double Precio_Unitario;
    double Monto_Total;
    string Medio_Envio;
    string Estado_Envio;
};

list<Venta> ventasList;
unordered_map<string, list<Venta>::iterator> ventasMap;

unordered_map<string, unordered_map<string, double>> ventasPorPaisCiudad;
unordered_map<string, unordered_map<string, double>> montoPorProductoPais;

// Prototipo de Funciones
void cargarDatosCSV();
void procesarDatos();
void mostrarMenu();
void mostrarTop5Ciudades();
void agregarVenta();
void eliminarVenta();
void modificarVenta();
void mostrarMontoProductoPais();

int main()
{
    cargarDatosCSV();
    procesarDatos();
    mostrarMenu();
    return 0;
}

void cargarDatosCSV()
{
    ifstream archivo("ventas_sudamerica.csv");
    string linea;
    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        Venta venta;

        // Leer campos básicos
        getline(ss, venta.ID_Venta, ',');
        getline(ss, venta.Fecha, ',');
        getline(ss, venta.Pais, ',');
        getline(ss, venta.Ciudad, ',');
        getline(ss, venta.Cliente, ',');
        getline(ss, venta.Producto, ',');
        getline(ss, venta.Categoria, ',');

        // Leer campos numéricos
        string temp;
        getline(ss, temp, ',');
        venta.Cantidad = stoi(temp);
        getline(ss, temp, ',');
        venta.Precio_Unitario = stod(temp);
        getline(ss, temp, ',');
        venta.Monto_Total = stod(temp);

        // Leer campos finales
        getline(ss, venta.Medio_Envio, ',');
        getline(ss, venta.Estado_Envio, ',');

        // Insertar en estructuras
        ventasList.push_back(venta);
        ventasMap[venta.ID_Venta] = prev(ventasList.end());
    }
    archivo.close();
}

void procesarDatos()
{
    auto inicio = chrono::high_resolution_clock::now();
    int condicionales = 0;

    // Resetear estructuras
    ventasPorPaisCiudad.clear();
    montoPorProductoPais.clear();

    for (const Venta &v : ventasList)
    {
        ventasPorPaisCiudad[v.Pais][v.Ciudad] += v.Monto_Total;

        montoPorProductoPais[v.Pais][v.Producto] += v.Monto_Total;

        if (!v.Pais.empty())
        {
            condicionales++;
        };
    }

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << "Procesamiento completado en " << duracion.count()
         << " segundos con " << condicionales << " condicionales" << endl;
}

void mostrarMenu()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "1. Top 5 ciudades por monto de ventas por pais" << endl;
        cout << "2. Monto total por producto y pais" << endl;
        cout << "3. Agregar nueva venta" << endl;
        cout << "4. Eliminar venta" << endl;
        cout << "5. Modificar venta" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            mostrarTop5Ciudades();
            break;
        case 2:
            mostrarMontoProductoPais();
            break;
        case 3:
            agregarVenta();
            procesarDatos();
            break;
        case 4:
            eliminarVenta();
            procesarDatos();
            break;
        case 5:
            modificarVenta();
            procesarDatos();
            break;
        }
        system("pause");
    } while (opcion != 6);
}

void mostrarTop5Ciudades()
{
    string pais;
    cout << "Ingrese el pais: ";
    cin >> pais;

    auto inicio = chrono::high_resolution_clock::now();
    int condicionales = 0;
    string algoritmo = "QuickSort (STL sort)";

    // Buscar el país en la estructura de datos
    auto it = ventasPorPaisCiudad.find(pais);
    condicionales++; // Contamos el condicional del if

    if (it == ventasPorPaisCiudad.end())
    {
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;

        cout << endl << "Pais no encontrado!" << endl;
        cout << "Tiempo de ejecución: " << duracion.count() << " s" << endl;
        cout << "Condicionales usados: " << condicionales << endl;
        cout << "Algoritmo usado: Búsqueda en mapa (O(log n))" << endl;
        return;
    }

    // Convertir el mapa de ciudades a vector y ordenar
    vector<pair<string, double>> ciudades;
    for (const auto &ciudad : it->second)
    {
        ciudades.emplace_back(ciudad.first, ciudad.second);
    }

    sort(ciudades.begin(), ciudades.end(),
         [](const pair<string, double> &a, const pair<string, double> &b)
         {
             return a.second > b.second;
         });

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    // Mostrar resultados
    cout << endl << "=== Resultados para " << pais << " ===" << endl;
    cout << "Tiempo de procesamiento: " << duracion.count() << " s" << endl;
    cout << "Condicionales usados: " << condicionales << endl;
    cout << "Algoritmo de ordenamiento: " << algoritmo << endl << endl;

    int limite = min(5, static_cast<int>(ciudades.size()));
    if (limite == 0)
    {
        cout << "No hay datos de ventas para ciudades en este país" << endl;
        return;
    }

    cout << "Top " << limite << " ciudades por ventas:" << endl;
    for (int i = 0; i < limite; ++i)
    {
        cout << i + 1 << ". " << ciudades[i].first
             << " - $" << fixed << setprecision(2) << ciudades[i].second << endl;
    }

    // Mensaje adicional con estilo del ejemplo
    cout << endl << "La ciudad con mayor monto total en " << pais
         << " es " << ciudades[0].first
         << " con $" << fixed << setprecision(2) << ciudades[0].second << endl;
}

void agregarVenta()
{
    Venta nueva;
    cout << "ID Venta: ";
    cin >> nueva.ID_Venta;
    cout << "Fecha (YYYY-MM-DD): ";
    cin >> nueva.Fecha;
    cout << "Pais: ";
    cin >> nueva.Pais;
    cout << "Ciudad: ";
    cin >> nueva.Ciudad;
    cout << "Cliente: ";
    cin >> nueva.Cliente;
    cout << "Producto: ";
    cin >> nueva.Producto;
    cout << "Categoria: ";
    cin >> nueva.Categoria;
    cout << "Cantidad: ";
    cin >> nueva.Cantidad;
    cout << "Precio Unitario: ";
    cin >> nueva.Precio_Unitario;
    cout << "Monto Total: ";
    cin >> nueva.Monto_Total;
    cout << "Medio de envio: ";
    cin >> nueva.Medio_Envio;
    cout << "Estado de envio: ";
    cin >> nueva.Estado_Envio;

    ventasList.push_back(nueva);
    ventasMap[nueva.ID_Venta] = prev(ventasList.end());
}

void eliminarVenta()
{
    string id;
    cout << "ID de venta a eliminar: ";
    cin >> id;

    auto it = ventasMap.find(id);

    if (it != ventasMap.end())
    {
        ventasList.erase(it->second);
        ventasMap.erase(it);
        cout << "Venta eliminada!" << endl;
    }
    else
    {
        cout << "Venta no encontrada!" << endl;
    }
}

void modificarVenta()
{
    string id;
    cout << "ID de venta a modificar: ";
    cin >> id;

    auto it = ventasMap.find(id);

    if (it != ventasMap.end())
    {
        Venta &v = *(it->second);
        cout << "Nuevo pais (actual: " << v.Pais << "): ";
        cin >> v.Pais;
        cout << "Nueva Ciudad (actual: " << v.Ciudad << "): ";
        cin >> v.Ciudad;
        cout << "Nueva Cliente (actual: " << v.Cliente << "): ";
        cin >> v.Cliente;
        cout << "Nueva Producto (actual: " << v.Producto << "): ";
        cin >> v.Producto;
        cout << "Nueva Categoria (actual: " << v.Categoria << "): ";
        cin >> v.Categoria;
        cout << "Nueva Cantidad (actual: " << v.Cantidad << "): ";
        cin >> v.Cantidad;
        cout << "Nueva Precio Unitario (actual: " << v.Precio_Unitario << "): ";
        cin >> v.Precio_Unitario;
        cout << "Nueva Monto Total (actual: " << v.Monto_Total << "): ";
        cin >> v.Monto_Total;
        cout << "Nueva Medio de envio (actual: " << v.Medio_Envio << "): ";
        cin >> v.Medio_Envio;
        cout << "Nueva Estado de envio (actual: " << v.Estado_Envio << "): ";
        cin >> v.Estado_Envio;

        return;
    }
    cout << "Venta no encontrada!" << endl;
}

void mostrarMontoProductoPais()
{
    string pais;

    cout << "Ingrese el pais: ";
    cin >> pais;

    auto inicio = chrono::high_resolution_clock::now();
    int condicionales = 0;
    string algoritmo = "Recorrido de tabla hash";

    // Buscar el pais en la estructura
    auto it_pais = montoPorProductoPais.find(pais);
    condicionales++;

    if (it_pais == montoPorProductoPais.end())
    {
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;

        cout << endl << "País no encontrado!" << endl;
        cout << "Tiempo ejecución: " << duracion.count() << " s" << endl;
        cout << "Condicionales usados: " << condicionales << endl;
        cout << "Algoritmo usado: Búsqueda en hash map (O(1) promedio)" << endl;
        return;
    }

    // Convertir a vector para ordenar
    vector<pair<string, double>> productos;

    for (const auto &entrada : it_pais->second)
    {
        productos.emplace_back(entrada.first, entrada.second);
        condicionales++; // Condicional del for
    }

    // Ordenar por monto descendente
    sort(productos.begin(), productos.end(),
         [](const pair<string, double> &a, const pair<string, double> &b)
         {
             return a.second > b.second;
         });

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    // Mostrar resultados
    cout << endl << "=== Monto por producto en " << pais << " ===" << endl;
    cout << "Tiempo procesamiento: " << duracion.count() << " s" << endl;
    cout << "Condicionales usados: " << condicionales << endl;
    cout << "Algoritmos usados:" << endl << "- " << algoritmo << endl << "- QuickSort (STL sort)" << endl << endl;

    for (const auto &entrada : productos)
    {
        cout << "- " << entrada.first << ": $"
             << fixed << setprecision(2) << entrada.second << endl;
    }

    if (!productos.empty())
    {
        cout << endl << "El producto con mayor monto en " << pais << " es "
             << productos[0].first << " con $"
             << fixed << setprecision(2) << productos[0].second << endl;
    }
}