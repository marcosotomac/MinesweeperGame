#include "JuegoBuscaminas.h"
#include <iostream>
#include <iomanip> // Para formatear la salida

// Función para mostrar el menú principal
void mostrarMenu() {
    std::cout << "\n";
    std::cout << "=============================\n";
    std::cout << "      🎮 MENU PRINCIPAL 🎮     \n";
    std::cout << "=============================\n";
    std::cout << "1️⃣  Iniciar Juego de Buscaminas\n";
    std::cout << "2️⃣  Ver Historial de Jugadores\n";
    std::cout << "3️⃣  Modo de Juego Automático 🤖\n";
    std::cout << "4️⃣  Salir del Programa\n";
    std::cout << "=============================\n";
    std::cout << "Ingrese su opción: ";
}

// Función para iniciar el juego
void iniciarJuego(Historial &historial) {
    std::string jugador;
    std::cout << "\n👤 Ingrese su nombre: ";
    std::cin >> jugador;

    // Crear instancia de JuegoBuscaminas
    JuegoBuscaminas juego(5, 5, 10, jugador);

    // Cargar historial y jugar
    juego.cargarHistorial("historial.txt");
    juego.jugar();
    juego.guardarHistorial("historial.txt");
}

// Función para mostrar el historial
void mostrarHistorial(Historial &historial) {
    std::cout << "\n=============================\n";
    std::cout << "    📜 HISTORIAL DE JUEGOS   \n";
    std::cout << "=============================\n";
    historial.mostrarHistorial();
    std::cout << "=============================\n";
}

// Función principal
int main() {
    int opcion;
    bool continuar = true;
    Historial historial;

    // Cargar historial al inicio
    historial.cargarHistorial("historial.txt");

    while (continuar) {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "\n=== 🚩 JUEGO DE BUSCAMINAS ===\n";
            iniciarJuego(historial);
            break;
            case 2:
                mostrarHistorial(historial);
            break;
            case 3: {
                std::string jugador = "AutoPlayer"; // Nombre del jugador automático
                JuegoBuscaminas juego(5, 5, 10, jugador);
                juego.cargarHistorial("historial.txt");
                juego.jugarAutomatico();
                juego.guardarHistorial("historial.txt");
                break;
            }
            case 4:
                std::cout << "\nGracias por jugar. ¡Hasta luego! 👋\n";
            continuar = false;
            break;
            default:
                std::cout << "❌ Opción inválida. Intente nuevamente.\n";
        }
    }

    // Guardar historial antes de salir
    historial.guardarHistorial("historial.txt");
    return 0;
}