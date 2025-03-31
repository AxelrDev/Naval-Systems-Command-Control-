#include <SFML/Graphics.hpp>

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ventana con SFML");

    // Crear un círculo
    sf::CircleShape circle(100.f); // Radio de 100 píxeles
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(300.f, 200.f); // Posición en la ventana

    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cerrar la ventana si se presiona el botón de cerrar
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la ventana con color negro
        window.clear(sf::Color::Black);

        // Dibujar el círculo
        window.draw(circle);

        // Mostrar lo que se ha dibujado
        window.display();
    }

    return 0;
}
