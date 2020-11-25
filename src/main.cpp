#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

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
        explosion.setOrigin(sf::Vector2f(48.0f, 48.0f));
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

    void setpos(sf::Vector2f pos) {
        explosion.setPosition(pos);
    }
};

class Rocket {
public:
    bool isLose;
    int score;
    bool ifNotGenerated;
    sf::Texture texture;
    sf::RectangleShape rect;
    Boom boom;

    Rocket() {
        isLose = false;
        score = 0;
        ifNotGenerated = false;
        texture.loadFromFile("res/bomb.png");

        rect.setSize(sf::Vector2f(texture.getSize().x * 5, texture.getSize().y * 5));
        rect.setTexture(&texture);
        rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
        rect.setPosition(-100.0f, -100.0f);
        rect.setRotation(90); // 70
    }

    void update(sf::RenderTarget &target, sf::Vector2f mousePos) {
        if(!ifNotGenerated) {
            isLose = false;
            float x = (rand() % 600) + 100.0f;
            rect.setPosition(x, -50.0f);
            ifNotGenerated = true;
        }

        rect.move(sf::Vector2f(0.0f, 5.0f));

        target.draw(rect);

        if(rect.getPosition().y > 550.0f) {
            boom.setpos(rect.getPosition());
            boom.update(target);
            if(!boom.isBoomed) {
                isLose = true;
                score = 0;
                boom.restart();
                ifNotGenerated = false;
            }
        }

        if(rect.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            score++;
            ifNotGenerated = false;
        }
    }
};

int main(int argv, char** argc) {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bomber", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    #ifdef __WIN32__
        sf::Image icon;
        icon.loadFromFile("res/bomb.png");
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    #endif

    sf::Texture textures[2];
    textures[0].loadFromFile("res/cursor.png");
    textures[1].loadFromFile("res/background.png");

    sf::RectangleShape cursor;
    cursor.setSize(sf::Vector2f(textures[0].getSize().x * 5, textures[0].getSize().y * 5));
    cursor.setPosition(0.0f, 0.0f);
    cursor.setTexture(&textures[0]);
    cursor.setOrigin(sf::Vector2f(cursor.getSize().x / 2, cursor.getSize().y / 2));

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(textures[1].getSize().x, textures[1].getSize().y));
    background.setPosition(0.0f, 0.0f);
    background.setTexture(&textures[1]);

    Rocket rocket;

    sf::Font font;
    font.loadFromFile("res/arial.ttf");

    sf::Text text;
    text.setPosition(0.0f, 0.0f);
    text.setCharacterSize(20);
    text.setFont(font);
    text.setString("Wynik: " + std::to_string(rocket.score));

    sf::Text loseText;
    loseText.setPosition(100.0f, 100.0f);
    loseText.setCharacterSize(40);
    loseText.setFont(font);
    loseText.setString("Przegrales!");

    sf::Clock loseClock;

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

        rocket.update(window, mouse);

        cursor.setPosition(mouse);
        window.draw(cursor);

        if(!rocket.isLose) {
            text.setString("Wynik: " + std::to_string(rocket.score));
            window.draw(text);
        } else {
            float loseTime = loseClock.getElapsedTime().asMilliseconds();
            loseClock.restart();
            std::cout << loseTime << "\n";
            window.draw(loseText);
            
        }
        
        

        window.display();
    }
}