//
// Created by Marco Soto Maceda on 1/12/24.
//

#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "Celda.h"

class Tablero {
private:
    int filas;
    int columnas;
    int totalMinas;
    std::vector<std::vector<Celda>> celdas;

    void generarMinas();
    void calcularMinasVecinas();

public:
    Tablero(int filas, int columnas, int totalMinas);
    bool revelarCelda(int fila, int columna);
    void marcarCelda(int fila, int columna);
    bool verificarVictoria() const;
    void mostrarTablero() const;
    bool contieneMina(int fila, int columna) const;
    const Celda &getCelda(int fila, int columna) const {
        return celdas[fila][columna];
    }

    // Métodos para obtener filas y columnas
    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
};

#endif