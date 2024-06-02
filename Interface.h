#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <SFML/Audio.hpp>
#include "Globals.h"
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
        float tpx = shape.getPosition().x + (shape.getSize().x - text.getCharacterSize() * text.getString().getSize()) / 2.0;
        float tpy = (shape.getPosition().y + shape.getSize().y / 2.0) - (text.getCharacterSize() / 2.0);
        text.setPosition(Vector2f(tpx, tpy));
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
    Font font;
    
    Text headText;
    Text generationText;
    vector<string> generationOptions;
    vector<vector<Text>> generationChoices;
    pair<int, int> generationSelected;

    Button button;
	Maze maze;
public:
    Interface() {
        generationOptions = { "DFS", "Prims", "Kruskals", "Wilsons" };
        generationChoices = {
            {Text(), Text()},
            {Text(), Text()}
        };
        generationSelected = { 0, 0 };

        // text initialization
        font.loadFromFile("ethnocentric.otf");
        headText.setFont(font);
        headText.setCharacterSize(20);
        headText.setString("Maze Visualizer");
        headText.setPosition(MAZE_WIDTH * TILE_SIZE + 20, 10);

        generationText.setFont(font);
        generationText.setCharacterSize(15);
        generationText.setString("\t\tChoose Maze\nGeneration Algorithm");
        generationText.setPosition(MAZE_WIDTH * TILE_SIZE + 15, 70);


        // buttons inialization
        button.setPosition(300, 250);
        button.setSize(150, 50);
        button.setCharacterSize(15);
        button.setText("Click Me");
        button.setFont("ethnocentric.otf"); 
        button.setNormalColor(sf::Color(100, 100, 100));
        button.setHoverColor(sf::Color(150, 150, 150));
        button.setClickedColor(sf::Color(200, 200, 200));
        button.setOnClick([]() {
        std::cout << "Button clicked!" << std::endl;
        });
    }

    void drawText(RenderWindow& window) {
        window.draw(headText);
        window.draw(generationText);

        for (int i = 0; i < generationChoices.size(); i++) {
            for (int j = 0; j < generationChoices[i].size(); j++) {
                int index = i * generationChoices[0].size() + j;
                generationChoices[i][j].setFont(font);
                generationChoices[i][j].setString(generationOptions[index]);
                generationChoices[i][j].setFillColor(Color::White);
                generationChoices[i][j].setCharacterSize(13);
                switch (index) {
                case 0:
                    generationChoices[i][j].setPosition(30, 0);
                    break;
                case 1:
                    generationChoices[i][j].setPosition(160, 0);
                    break;
                case 2:
                    generationChoices[i][j].setPosition(0, generationChoices[i][j].getCharacterSize() + 15);
                    break;
                case 3:
                    generationChoices[i][j].setPosition(150, generationChoices[i][j].getCharacterSize() + 15);
                    break;
                }
                generationChoices[i][j].move(MAZE_WIDTH * TILE_SIZE + 30, 150);

                if (generationSelected.first == i && generationSelected.second == j) {
                    generationChoices[i][j].setFillColor(Color(0x04, 0xd9, 0xff));
                    generationChoices[i][j].setCharacterSize(15);
                    generationChoices[i][j].move(-5, -5);
                }
                window.draw(generationChoices[i][j]);
            }
        }
    }

    void drawButtons(RenderWindow& window) {
        button.update(window);
        button.render(window);
    }

	void control(RenderWindow& window) {
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (generationSelected.first > 0) {
                generationSelected.first--;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (generationSelected.first < generationChoices.size() - 1) {
                generationSelected.first++;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (generationSelected.second > 0) {
                generationSelected.second--;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (generationSelected.second < generationChoices[0].size() - 1) {
                generationSelected.second++;
            }
        }

		maze.draw(window);
        drawButtons(window);
        drawText(window);
	}
};