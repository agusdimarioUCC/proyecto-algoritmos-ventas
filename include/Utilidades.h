#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <chrono>
#include <string>

using namespace std;

class Utilidades {
private:
    long long ifCount;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

public:
    Utilidades() : ifCount(0) {}

    // Inicia medición de tiempo y resetea contador de if
    void start() {
        ifCount = 0;
        startTime = std::chrono::high_resolution_clock::now();
    }

    // Invocar cada vez que se use un if
    void contarIf() {
        ifCount++;
    }

    // Finaliza medición, imprime métricas
    void end(const string &nombreProceso, const string &estructura, const string &notacion) {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        cout << "Proceso: " << nombreProceso << endl;
        cout << "Estructura: " << estructura << " | O(" << notacion << ")" << endl;
        cout << "Tiempo de ejecución: " << duracion << " microsegundos" << endl;
        cout << "Cantidad de if: " << ifCount << endl;
        cout << "-------------------------------------" << endl;
    }
};

#endif // UTILIDADES_H