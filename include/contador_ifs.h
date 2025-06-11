#ifndef CONTADOR_IFS_H
#define CONTADOR_IFS_H

#include <string>
#include <iostream>

// Variable global para contar los IFs
extern int contadorIfs;
extern int contadorIfsProceso; // Para medir un proceso específico

// Funciones auxiliares
inline void incrementarContadorIf() {
    contadorIfs++;
    contadorIfsProceso++;
}

inline void iniciarConteoIfs() {
    contadorIfsProceso = 0;
}

inline void mostrarEstadisticasProceso(const std::string& nombreProceso) {
    std::cout << "\n--- Estadísticas: " << nombreProceso << " ---" << std::endl;
    std::cout << "IFs ejecutados en este proceso: " << contadorIfsProceso << std::endl;
    std::cout << "Total de IFs del programa: " << contadorIfs << std::endl;
}

#endif // CONTADOR_IFS_H