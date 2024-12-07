//
// Created by Marco Soto Maceda on 1/12/24.
//

#include "Celda.h"

Celda::Celda() : tieneMina(false), estaRevelada(false), estaMarcada(false), minasVecinas(0) {}

void Celda::colocarMina() {
    tieneMina = true;
}

bool Celda::esMina() const {
    return tieneMina;
}

void Celda::revelar() {
    estaRevelada = true;
}

bool Celda::esRevelada() const {
    return estaRevelada;
}

void Celda::marcar() {
    estaMarcada = !estaMarcada;
}

bool Celda::esMarcada() const {
    return estaMarcada;
}

void Celda::setMinasVecinas(int minas) {
    minasVecinas = minas;
}

int Celda::getMinasVecinas() const {
    return minasVecinas;
}