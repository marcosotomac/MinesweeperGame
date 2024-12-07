//
// Created by Marco Soto Maceda on 1/12/24.
//

#ifndef JUEGOBUSCAMINAS_H
#define JUEGOBUSCAMINAS_H

#include "Tablero.h"
#include "Historial.h"
#include <string>

class JuegoBuscaminas {
private:
    Tablero tablero;
    Historial historial;
    std::string jugadorActual;
    bool juegoTerminado;

public:
    JuegoBuscaminas(int filas, int columnas, int totalMinas, const std::string &jugador);
    void jugar(); // Modo interactivo
    void jugarAutomatico(); // Declaración del modo automático
    void guardarHistorial(const std::string &archivo) const;
    void cargarHistorial(const std::string &archivo);
    Tablero &getTablero() { return tablero; } // Método para acceder al tablero
};

#endif