#include "Ship.h"
#include <fstream>
#include <iomanip>
#include <iostream>

void Ship::logOperation(const std::string& type, int iterations, double time) {
    // Abrimos (o creamos) un archivo de log
    std::ofstream logFile("battle_log.txt", std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Error opening battle log file." << std::endl;
        return;
    }

    // Escribimos los datos de la operación
    logFile << "=== Operation Log ===" << std::endl;
    logFile << "Ship: " << name << std::endl;
    logFile << "Operation: " << type << std::endl;
    logFile << "Iterations: " << iterations << std::endl;
    logFile << std::fixed << std::setprecision(6)
            << "Execution Time: " << time << " seconds" << std::endl;
    logFile << "Damage: " << calculateDamage(iterations) << std::endl;
    logFile << "-----------------------" << std::endl;

    logFile.close();
}
