#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Maze.h"

using namespace sf;
using namespace std;

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color clickedColor;
    std::function<void()> onClick;
    bool isHovered;
    bool isClicked;

public:
    Button(float x, float y, float width, float height, const std::string& buttonText, std::function<void()> onClick)
        : onClick(onClick), isHovered(false), isClicked(false) {

        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));

        // Load font (Make sure the font file is in the correct path)
        font.loadFromFile("ethnocentric.otf");

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        // Center the text
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x + width / 2.0f, y + height / 2.0f);

        // Set button colors
        normalColor = sf::Color(100, 100, 100);
        hoverColor = sf::Color(150, 150, 150);
        clickedColor = sf::Color(200, 200, 200);

        shape.setFillColor(normalColor);
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
                    onClick();
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
    Interface(): button(300, 250, 200, 100, "Click Me", []() {
        std::cout << "Button clicked!" << std::endl;
        }) {

    }
	void control(RenderWindow& window) {
		maze.draw(window);
        button.update(window);
        button.render(window);
	}
};