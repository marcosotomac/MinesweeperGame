#include "Tablero.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


#include <iomanip> // Para std::setw
void limpiarPantalla() {
#ifdef _WIN32
    system("cls"); //
#else
    system("clear"); //
#endif
}

Tablero::Tablero(int filas, int columnas, int totalMinas)
    : filas(filas), columnas(columnas), totalMinas(totalMinas), celdas(filas, std::vector<Celda>(columnas)) {
    generarMinas();
    calcularMinasVecinas();
}

bool Tablero::contieneMina(int fila, int columna) const {
    // Verificar límites del tablero
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return false; // Coordenadas inválidas
    }

    // Retornar si la celda contiene una mina
    return celdas[fila][columna].esMina();
}

void Tablero::generarMinas() {
    srand(time(0));
    int minasColocadas = 0;
    while (minasColocadas < totalMinas) {
        int fila = rand() % filas;
        int columna = rand() % columnas;
        if (!celdas[fila][columna].esMina()) {
            celdas[fila][columna].colocarMina();
            minasColocadas++;
        }
    }
}

void Tablero::calcularMinasVecinas() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (celdas[i][j].esMina()) continue;

            int minas = 0;
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int ni = i + x, nj = j + y;
                    if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas && celdas[ni][nj].esMina()) {
                        minas++;
                    }
                }
            }
            celdas[i][j].setMinasVecinas(minas);
        }
    }
}

bool Tablero::revelarCelda(int fila, int columna) {
    // Validar límites del tablero
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        std::cout << "❌ Coordenadas fuera del tablero. Intente de nuevo.\n";
        return false;
    }

    // Verificar si la celda ya está revelada
    if (celdas[fila][columna].esRevelada()) {
        std::cout << "⚠️ Celda ya revelada. Elija otra.\n";
        return false;
    }

    // Revelar la celda
    celdas[fila][columna].revelar();

    // Si es una mina, se pierde el juego
    if (celdas[fila][columna].esMina()) {
        return true;  // Indica fin del juego
    }

    // Si no hay minas vecinas, revelar las celdas vecinas recursivamente
    if (celdas[fila][columna].getMinasVecinas() == 0) {
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                int nuevaFila = fila + x;
                int nuevaColumna = columna + y;
                if (nuevaFila >= 0 && nuevaFila < filas &&
                    nuevaColumna >= 0 && nuevaColumna < columnas &&
                    !celdas[nuevaFila][nuevaColumna].esRevelada()) {
                    revelarCelda(nuevaFila, nuevaColumna);
                    }
            }
        }
    }
    return false;
}

void Tablero::marcarCelda(int fila, int columna) {
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas) {
        celdas[fila][columna].marcar();
    }
}

bool Tablero::verificarVictoria() const {
    for (const auto &fila : celdas) {
        for (const auto &celda : fila) {
            if (!celda.esMina() && !celda.esRevelada()) {
                return false;
            }
        }
    }
    return true;
}

#include "Tablero.h"
#include <iostream>
#include <iomanip> // Para formatear salida

void Tablero::mostrarTablero() const {
    limpiarPantalla(); // Limpia la consola antes de imprimir el tablero
    std::cout << "\n   "; // Espacio para bordes superiores

    // Encabezado de columnas
    for (int j = 0; j < columnas; ++j) {
        std::cout << std::setw(3) << j;
    }
    std::cout << "\n";

    // Línea separadora superior
    std::cout << "   " << std::string(columnas * 3, '-') << "\n";

    // Filas del tablero
    for (int i = 0; i < filas; ++i) {
        std::cout << std::setw(2) << i << " |"; // Etiqueta de fila con borde izquierdo

        for (int j = 0; j < columnas; ++j) {
            const Celda &celda = celdas[i][j];

            if (celda.esRevelada()) {
                if (celda.esMina()) {
                    std::cout << " 💣"; // Mina
                } else if (celda.getMinasVecinas() == 0) {
                    std::cout << "   "; // Celda vacía
                } else {
                    std::cout << std::setw(2) << celda.getMinasVecinas();
                }
            } else if (celda.esMarcada()) {
                std::cout << " 🚩"; // Marcada como mina
            } else {
                std::cout << " ⬜"; // Celda oculta
            }
        }

        std::cout << " |\n"; // Borde derecho al final de la fila
    }

    // Línea separadora inferior
    std::cout << "   " << std::string(columnas * 3, '-') << "\n";
}