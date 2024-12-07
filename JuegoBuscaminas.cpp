#include "JuegoBuscaminas.h"
#include <iostream>
#include <chrono>

JuegoBuscaminas::JuegoBuscaminas(int filas, int columnas, int totalMinas, const std::string &jugador)
    : tablero(filas, columnas, totalMinas), jugadorActual(jugador), juegoTerminado(false) {}

#include <cstdlib> // Para srand y rand
#include <ctime>   // Para inicializar srand

#include <set> // Para registrar celdas reveladas


void JuegoBuscaminas::jugarAutomatico() {
    std::cout << "\n=== 🤖 MODO AUTOMÁTICO ===\n";
    std::cout << "El programa intentará ganar...\n";

    srand(static_cast<unsigned>(time(0))); // Inicializar generador aleatorio
    std::set<std::pair<int, int>> reveladas; // Celdas ya reveladas
    std::set<std::pair<int, int>> marcadas;  // Celdas marcadas como minas

    juegoTerminado = false;

    while (!juegoTerminado) {
        bool accionRealizada = false;

        // Recorrer el tablero para buscar celdas reveladas
        for (int i = 0; i < tablero.getFilas(); ++i) {
            for (int j = 0; j < tablero.getColumnas(); ++j) {
                if (reveladas.count({i, j}) > 0) continue; // Saltar celdas ya procesadas

                const Celda &celda = tablero.getCelda(i, j);
                if (!celda.esRevelada()) continue; // Solo procesar celdas reveladas

                int minasVecinas = celda.getMinasVecinas();
                if (minasVecinas == 0) continue; // No hay información útil para esta celda

                // Analizar las vecinas
                std::vector<std::pair<int, int>> ocultas;
                std::vector<std::pair<int, int>> marcadasVecinas;

                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int ni = i + x, nj = j + y;
                        if (ni >= 0 && ni < tablero.getFilas() &&
                            nj >= 0 && nj < tablero.getColumnas()) {
                            if (!tablero.getCelda(ni, nj).esRevelada() &&
                                marcadas.count({ni, nj}) == 0) {
                                ocultas.push_back({ni, nj});
                            }
                            if (marcadas.count({ni, nj}) > 0) {
                                marcadasVecinas.push_back({ni, nj});
                            }
                        }
                    }
                }

                // Marcar celdas como minas si corresponde
                if (marcadasVecinas.size() + ocultas.size() == minasVecinas) {
                    for (const auto &[vi, vj] : ocultas) {
                        if (marcadas.count({vi, vj}) == 0) {
                            marcadas.insert({vi, vj});
                            std::cout << "🚩 Marcada celda como mina: (" << vi << ", " << vj << ").\n";
                            tablero.marcarCelda(vi, vj);
                            accionRealizada = true;
                            tablero.mostrarTablero();
                        }
                    }
                }

                // Revelar celdas seguras si corresponde
                if (marcadasVecinas.size() == minasVecinas) {
                    for (const auto &[vi, vj] : ocultas) {
                        if (!tablero.getCelda(vi, vj).esRevelada() &&
                            marcadas.count({vi, vj}) == 0) {
                            std::cout << "✅ Revelada celda segura: (" << vi << ", " << vj << ").\n";
                            if (tablero.revelarCelda(vi, vj)) {
                                std::cout << "💥 El programa pisó una mina en: (" << vi << ", " << vj << ").\n";
                                tablero.mostrarTablero();
                                historial.registrarPartida(jugadorActual, false);
                                juegoTerminado = true;
                                return;
                            }
                            reveladas.insert({vi, vj});
                            accionRealizada = true;
                            tablero.mostrarTablero();
                        }
                    }
                }

                if (accionRealizada) break;
            }
            if (accionRealizada) break;
        }

        // Si no se realizó ninguna acción, elegir una celda aleatoria
        if (!accionRealizada) {
            int fila, columna;
            do {
                fila = rand() % tablero.getFilas();
                columna = rand() % tablero.getColumnas();
            } while (reveladas.count({fila, columna}) > 0 || marcadas.count({fila, columna}) > 0);

            std::cout << "🔍 Intentando revelar celda aleatoria: (" << fila << ", " << columna << ").\n";
            if (tablero.revelarCelda(fila, columna)) {
                std::cout << "💥 El programa pisó una mina en: (" << fila << ", " << columna << ").\n";
                tablero.mostrarTablero();
                historial.registrarPartida(jugadorActual, false);
                juegoTerminado = true;
                return;
            }
            reveladas.insert({fila, columna});
            tablero.mostrarTablero();
        }

        // Verificar si ganó
        if (tablero.verificarVictoria()) {
            std::cout << "🎉 El programa ganó el juego marcando y revelando todas las celdas seguras.\n";
            historial.registrarPartida(jugadorActual, true);
            juegoTerminado = true;
        }
    }
}


void JuegoBuscaminas::jugar() {
    auto inicio = std::chrono::steady_clock::now();
    std::cout << "🎮 Jugador actual: " << jugadorActual << "\n";

    while (!juegoTerminado) {
        tablero.mostrarTablero();
        int fila, columna;
        char accion;

        std::cout << "Seleccione una acción (R para revelar, M para marcar): ";
        std::cin >> accion;

        if (accion != 'R' && accion != 'M') {
            std::cout << "❌ Acción no válida. Use 'R' para revelar o 'M' para marcar.\n";
            continue;
        }

        std::cout << "Ingrese las coordenadas (fila columna): ";
        std::cin >> fila >> columna;

        // Manejar acción de revelar
        if (accion == 'R') {
            if (tablero.revelarCelda(fila, columna)) {
                tablero.mostrarTablero();
                std::cout << "💥 BOOM! Has perdido.\n";
                historial.registrarPartida(jugadorActual, false);
                juegoTerminado = true;
            }
        }
        // Manejar acción de marcar
        else if (accion == 'M') {
            if (fila < 0 || fila >= tablero.getFilas() || columna < 0 || columna >= tablero.getColumnas()) {
                std::cout << "❌ Coordenadas fuera del tablero. Intente de nuevo.\n";
            } else {
                tablero.marcarCelda(fila, columna);
                std::cout << "🚩 Celda marcada.\n";
            }
        }

        // Verificar victoria
        if (tablero.verificarVictoria()) {
            tablero.mostrarTablero();
            std::cout << "🎉 ¡Felicidades, ganaste! 🎉\n";
            historial.registrarPartida(jugadorActual, true);
            juegoTerminado = true;
        }
    }

    auto fin = std::chrono::steady_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::seconds>(fin - inicio).count();
    std::cout << "⏳ Duración de la partida: " << duracion << " segundos.\n";
}

void JuegoBuscaminas::guardarHistorial(const std::string &archivo) const {
    historial.guardarHistorial(archivo);
}

void JuegoBuscaminas::cargarHistorial(const std::string &archivo) {
    historial.cargarHistorial(archivo);
}

