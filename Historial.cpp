//
// Created by Marco Soto Maceda on 1/12/24.
//
#include "Historial.h"


void Historial::registrarPartida(const std::string &nombre, bool victoria) {
    if (jugadores.find(nombre) == jugadores.end()) {
        jugadores[nombre] = Jugador(nombre); // Constructor con nombre
    }

    if (victoria) {
        jugadores[nombre].registrarVictoria();
    } else {
        jugadores[nombre].registrarDerrota();
    }
}


void Historial::mostrarHistorial() const {
    std::cout << "\n📜 Historial de Jugadores:\n";
    for (const auto &entry : jugadores) {
        const Jugador &jugador = entry.second;
        std::cout << "Jugador: " << jugador.getNombre() << "\n";
        std::cout << "  Victorias: " << jugador.getVictorias() << "\n";
        std::cout << "  Derrotas: " << jugador.getDerrotas() << "\n";
    }
}


void Historial::guardarHistorial(const std::string &archivo) const {
    std::ofstream file(archivo);
    if (!file) {
        std::cerr << "Error al guardar el historial en el archivo.\n";
        return;
    }

    for (const auto &entry : jugadores) {
        const Jugador &jugador = entry.second;
        file << jugador.getNombre() << " " << jugador.getVictorias() << " " << jugador.getDerrotas() << "\n";
    }
    file.close();
}


void Historial::cargarHistorial(const std::string &archivo) {
    std::ifstream file(archivo);
    if (!file) {
        std::cerr << "No se pudo cargar el historial desde el archivo.\n";
        return;
    }

    jugadores.clear();
    std::string nombre;
    int victorias, derrotas;

    while (file >> nombre >> victorias >> derrotas) {
        Jugador jugador(nombre);
        for (int i = 0; i < victorias; ++i) jugador.registrarVictoria();
        for (int i = 0; i < derrotas; ++i) jugador.registrarDerrota();
        jugadores[nombre] = jugador;
    }
    file.close();
}