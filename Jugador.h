//
// Created by Marco Soto Maceda on 1/12/24.
//

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
private:
    std::string nombre;
    int victorias;
    int derrotas;

public:
    // Constructor por defecto
    Jugador() : nombre(""), victorias(0), derrotas(0) {}

    // Constructor con argumentos
    Jugador(const std::string &nombre) : nombre(nombre), victorias(0), derrotas(0) {}

    // Métodos de modificación
    void registrarVictoria() { victorias++; }
    void registrarDerrota() { derrotas++; }

    // Métodos de acceso
    std::string getNombre() const { return nombre; }
    int getVictorias() const { return victorias; }
    int getDerrotas() const { return derrotas; }
};

#endif