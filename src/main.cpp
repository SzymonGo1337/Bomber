#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Boom {
public:
    bool isBoomed = false;
    int dif = 0;
    sf::Texture txt;
    sf::RectangleShape explosion;

    Boom() {
        txt.loadFromFile("res/explosion.png");
        explosion.setSize(sf::Vector2f(96.0f, 96.0f));
        explosion.setPosition(0.0f, 0.0f);
        explosion.setTexture(&txt);
        explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
    }

    void update(sf::RenderTarget &target) {
        if(!isBoomed) {
            sf::Clock clock;

            if(dif > 1152) {
                isBoomed = true;
                dif = 0;
            }

            if(clock.getElapsedTime().asMilliseconds() <= 300.0f && clock.getElapsedTime().asMilliseconds() >= 0.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 600.0f && clock.getElapsedTime().asMilliseconds() >= 300.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 900.0f && clock.getElapsedTime().asMilliseconds() >= 600.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 1200.0f && clock.getElapsedTime().asMilliseconds() >= 900.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 1500.0f && clock.getElapsedTime().asMilliseconds() >= 1200.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 1800.0f && clock.getElapsedTime().asMilliseconds() >= 1500.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 2100.0f && clock.getElapsedTime().asMilliseconds() >= 1800.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 2400.0f && clock.getElapsedTime().asMilliseconds() >= 2100.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 2700.0f && clock.getElapsedTime().asMilliseconds() >= 2400.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 3000.0f && clock.getElapsedTime().asMilliseconds() >= 2700.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 3300.0f && clock.getElapsedTime().asMilliseconds() >= 3000.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() <= 3600.0f && clock.getElapsedTime().asMilliseconds() >= 3300.0f) {
                dif = dif + 96;
                explosion.setTextureRect(sf::IntRect(dif, 0, 96, 96));
            } else if(clock.getElapsedTime().asMilliseconds() > 3600.0f) {
                isBoomed = true;
                dif = 0;
                clock.restart();
            }

            target.draw(explosion);
        }
    }

    void restart() {
        isBoomed = false;
    }
};

int main(int argv, char** argc) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bomber", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::Texture textures[7];
    textures[0].loadFromFile("res/cursor.png");
    textures[1].loadFromFile("res/background.png");
    textures[2].loadFromFile("res/bomb.png");
    textures[3].loadFromFile("res/explosion.png");

    sf::RectangleShape cursor;
    cursor.setSize(sf::Vector2f(textures[0].getSize().x * 5, textures[0].getSize().y * 5));
    cursor.setPosition(0.0f, 0.0f);
    cursor.setTexture(&textures[0]);
    cursor.setOrigin(sf::Vector2f(cursor.getSize().x / 2, cursor.getSize().y / 2));

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(textures[1].getSize().x, textures[1].getSize().y));
    background.setPosition(0.0f, 0.0f);
    background.setTexture(&textures[1]);

    Boom boom;

    bool focus = true;
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.type == sf::Event::GainedFocus) { focus = true; }
            if(event.type == sf::Event::LostFocus) { focus = false; }
        }

        sf::Vector2f mouse;
        if(focus) { mouse = sf::Vector2f(sf::Mouse::getPosition(window)); }

        window.clear(sf::Color::Green);
        window.draw(background);

        boom.update(window);

        cursor.setPosition(mouse);
        window.draw(cursor);

        window.display();
    }
}