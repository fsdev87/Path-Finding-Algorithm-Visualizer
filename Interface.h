#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <SFML/Audio.hpp>
#include "Maze.h"

using namespace sf;
using namespace std;

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color clickedColor;
    std::function<void()> onClick;
    bool isHovered;
    bool isClicked;

public:
    Button()
        : normalColor(sf::Color(100, 100, 100)),
        hoverColor(sf::Color(150, 150, 150)),
        clickedColor(sf::Color(200, 200, 200)),
        isHovered(false),
        isClicked(false) {
    }

    Button(float x, float y, float width, float height, const std::string& buttonText, std::function<void()> onClick)
        : onClick(onClick), isHovered(false), isClicked(false) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));

        text.setFillColor(sf::Color::White);

        // Center the text
        setText(buttonText);

        // Set button colors
        normalColor = sf::Color(100, 100, 100);
        hoverColor = sf::Color(150, 150, 150);
        clickedColor = sf::Color(200, 200, 200);

        shape.setFillColor(normalColor);
    }

    void setCharacterSize(int n) {
        text.setCharacterSize(n);
        setText(text.getString());
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
        text.setPosition(x + shape.getSize().x / 2.0f, y + shape.getSize().y / 2.0f);
    }

    void setSize(float width, float height) {
        shape.setSize(sf::Vector2f(width, height));
        text.setPosition(shape.getPosition().x + width / 2.0f, shape.getPosition().y + height / 2.0f);
    }

    void setText(const std::string& buttonText) {
        text.setString(buttonText);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setPosition(shape.getPosition());
    }

    void setFont(const std::string& fontPath) {
        if (!font.loadFromFile(fontPath)) {
            std::cerr << "Failed to load font '" << fontPath << "'" << std::endl;
        }
        else {
            text.setFont(font);
        }
    }

    void setSound(const std::string& soundPath) {
        if (!buffer.loadFromFile(soundPath)) {
            std::cerr << "Failed to load sound '" << soundPath << "'" << std::endl;
        }
        else {
            sound.setBuffer(buffer);
        }
    }

    void setNormalColor(const sf::Color& color) {
        normalColor = color;
        shape.setFillColor(normalColor);
    }

    void setHoverColor(const sf::Color& color) {
        hoverColor = color;
    }

    void setClickedColor(const sf::Color& color) {
        clickedColor = color;
    }

    void setOnClick(std::function<void()> handler) {
        onClick = handler;
    }

    void update(const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonBounds = shape.getGlobalBounds();

        if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                isClicked = true;
                shape.setFillColor(clickedColor);
            }
            else {
                if (isClicked) {
                    isClicked = false;
                    if (onClick) onClick();
                    sound.play();
                }
                isHovered = true;
                shape.setFillColor(hoverColor);
            }
        }
        else {
            isHovered = false;
            shape.setFillColor(normalColor);
        }
    }

    void render(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
};


class Interface {
private:
    Button button;
	Maze maze;
public:
    Interface() {
        button.setPosition(300, 250);
        button.setSize(200, 100);
        button.setCharacterSize(20);
        button.setText("Click Me");
        button.setFont("ethnocentric.otf"); 
        button.setNormalColor(sf::Color(100, 100, 100));
        button.setHoverColor(sf::Color(150, 150, 150));
        button.setClickedColor(sf::Color(200, 200, 200));
        button.setOnClick([]() {
        std::cout << "Button clicked!" << std::endl;
        });
    }
	void control(RenderWindow& window) {
		maze.draw(window);
        button.update(window);
        button.render(window);
	}
};