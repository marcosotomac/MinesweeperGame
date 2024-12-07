//
// Created by Marco Soto Maceda on 1/12/24.
//

#ifndef CELDA_H
#define CELDA_H

class Celda {
private:
    bool tieneMina;
    bool estaRevelada;
    bool estaMarcada;
    int minasVecinas;

public:
    Celda();
    void colocarMina();
    bool esMina() const;
    void revelar();
    bool esRevelada() const;
    void marcar();
    bool esMarcada() const;
    void setMinasVecinas(int minas);
    int getMinasVecinas() const;
};

#endif