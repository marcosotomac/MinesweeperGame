//
// Created by Marco Soto Maceda on 1/12/24.
//

#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "Jugador.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>

class Historial {
private:
    std::map<std::string, Jugador> jugadores;

public:
    void registrarPartida(const std::string &nombre, bool victoria);
    void mostrarHistorial() const;
    void guardarHistorial(const std::string &archivo) const;
    void cargarHistorial(const std::string &archivo);
};

#endif