#ifndef SHIP_HPP
#define SHIP_HPP

#define LIFE 3
#define DAMAGE 1

class Ship {
public:
    // Constructor: recibe la posición (row, col), la vida y el daño.
    Ship(int row, int col, int vida, int damage, int level);
    Ship();
    // Retorna true si la casilla (row, col) es la posición del barco.
    bool occupies(int row, int col) const;
    
    // Aplica daño al barco (por ejemplo, 1 punto por disparo) y retorna true si el barco se hunde.
    bool applyDamage(int damageAmount);
    
    // Getters para la vida y el daño.
    int getVida() const;
    int getDamage() const;
    
    // Getters y setter para la posición.
    int getRow() const;
    int getCol() const;
    void setPosition(int row, int col);

    // Get level
    int getLevel();

    // Getter and Setter for empty
    bool getEmpty();
    void setEmpty(bool empty);

private:
    int row;
    int col;
    int vida;    // Cantidad de vida del barco.
    int damage;  // Daño que puede causar (para futuras lógicas, por ejemplo en ataques especiales).
    int level; 
    bool empty;
};

#endif // SHIP_HPP
