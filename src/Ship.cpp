#include "Ship.h"

Ship::Ship(int row, int col, int length, bool horizontal)
    : startRow(row), startCol(col), length(length), horizontal(horizontal), hits(length, false) {}

bool Ship::occupies(int row, int col) const {
    if (horizontal) {
        return (row == startRow) && (col >= startCol && col < startCol + length);
    } else {
        return (col == startCol) && (row >= startRow && row < startRow + length);
    }
}

bool Ship::hitAt(int row, int col) {
    if (!occupies(row, col))
        return false;
    int index = horizontal ? col - startCol : row - startRow;
    if (!hits[index]) {
        hits[index] = true;
        return true;
    }
    return false;
}

bool Ship::isSunk() const {
    for (bool hit : hits) {
        if (!hit)
            return false;
    }
    return true;
}

int Ship::getLength() const {
    return length;
}
