#ifndef SHIP_H
#define SHIP_H

#include <vector>

class Ship {
public:
    // Constructor: crea un barco que inicia en (row, col), de longitud "length" y orientación.
    // Si horizontal es true, se extiende hacia la derecha; de lo contrario, hacia abajo.
    Ship(int row, int col, int length, bool horizontal);
    
    // Retorna true si la celda (row, col) forma parte del barco.
    bool occupies(int row, int col) const;
    
    // Procesa un disparo en (row, col); si la celda forma parte del barco y aún no estaba impactada,
    // marca la posición y retorna true.
    bool hitAt(int row, int col);
    
    // Retorna true si todas las celdas del barco han sido impactadas.
    bool isSunk() const;

    // Retorna la longitud del barco.
    int getLength() const;

private:
    int startRow;
    int startCol;
    int length;
    bool horizontal; // true: horizontal, false: vertical
    std::vector<bool> hits; // Registra el impacto de cada segmento (inicialmente todos false).
};

#endif // SHIP_H
