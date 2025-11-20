#include <SFML/Graphics.hpp>
#include <optional> // pas toujours nécessaire mais ça clarifie

int main() {
    // SFML 3 : VideoMode prend un Vector2u
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "SFML + VS Code");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    // SFML 3 : setPosition prend un Vector2f
    shape.setPosition({300.f, 200.f});

    while (window.isOpen()) {
        // SFML 3 : pollEvent() renvoie std::optional<sf::Event>
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }

    return 0;
}
