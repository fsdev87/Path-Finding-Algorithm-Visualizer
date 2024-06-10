#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <SFML/Audio.hpp>
#include <functional>
#include "Globals.h"
#include "Maze.h"

using namespace sf;
using namespace std;

class Button {
private:
    RectangleShape shape;
    Text text;
    Font font;
    SoundBuffer buffer;
    Sound sound;
    Color normalColor;
    Color hoverColor;
    Color clickedColor;
    function<void()> onClick;
    bool isHovered;
    bool isClicked;

public:
    Button()
        : normalColor(Color(100, 100, 100)),
        hoverColor(Color(150, 150, 150)),
        clickedColor(Color(200, 200, 200)),
        isHovered(false),
        isClicked(false) {
    }

    Button(float x, float y, float width, float height, const std::string& buttonText, std::function<void()> onClick)
        : onClick(onClick), isHovered(false), isClicked(false) {
        shape.setPosition(x, y);
        shape.setSize(Vector2f(width, height));

        text.setFillColor(Color::White);

        // Center the text
        setText(buttonText);

        // Set button colors
        normalColor = Color(100, 100, 100);
        hoverColor = Color(150, 150, 150);
        clickedColor = Color(200, 200, 200);

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
        shape.setSize(Vector2f(width, height));
        text.setPosition(shape.getPosition().x + width / 2.0f, shape.getPosition().y + height / 2.0f);
    }

    void setText(const std::string& buttonText) {
        text.setString(buttonText);
        FloatRect textRect = text.getLocalBounds();
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

    void setNormalColor(const Color& color) {
        normalColor = color;
        shape.setFillColor(normalColor);
    }

    void setHoverColor(const Color& color) {
        hoverColor = color;
    }

    void setClickedColor(const Color& color) {
        clickedColor = color;
    }

    void setOnClick(const std::function<void()>& onClick) {
        this->onClick = onClick;
    }

    template <typename Callable, typename... Args>
    void setOnClick(Callable&& func, Args&&... args) {
        onClick = bind(forward<Callable>(func), forward<Args>(args)...);
    }

    void update(const RenderWindow& window) {
        Vector2i mousePos = Mouse::getPosition(window);
        FloatRect buttonBounds = shape.getGlobalBounds();

        if (buttonBounds.contains(static_cast<Vector2f>(mousePos))) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                isClicked = true;
                shape.setFillColor(clickedColor);
                text.setFillColor(hoverColor);
            }
            else {
                if (isClicked) {
                    isClicked = false;
                    if (onClick) onClick();
                    sound.play();
                }
                isHovered = true;
                shape.setFillColor(hoverColor);
                text.setFillColor(clickedColor);
            }
        }
        else {
            isHovered = false;
            shape.setFillColor(normalColor);
            text.setFillColor(Color::White);
        }
    }

    void render(RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
};


void generateHandler(Maze& maze, pair<int, int>& choice) {
    maze.setChoiceGenerate(choice.first * 2 + choice.second + 1);
}

void resetHandler(Maze& maze) {
    maze.reset();
}

class SelectButton {
private:
    CircleShape outer;
    CircleShape inner;
public:
    bool selected;
    SelectButton() {
        outer.setFillColor(Color::White);
        outer.setRadius(8);

        inner.setFillColor(Color(0x0e, 0x19, 0x1f));
        inner.setRadius(6);

        selected = false;
    }

    void setPosition(float x, float y) {
        outer.setPosition(Vector2f(x, y));
        inner.setPosition(outer.getPosition());
        inner.move(2, 2);
    }

    void update(const RenderWindow& window, bool& otherSelected) {
        Vector2i mousePos = Mouse::getPosition(window);
        FloatRect buttonBounds = inner.getGlobalBounds();

        if (buttonBounds.contains(static_cast<Vector2f>(mousePos))) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                inner.setFillColor(Color(0x04, 0xd9, 0xff));
                selected = true;
                otherSelected = false;
            }
        }

        if (!selected) {
            inner.setFillColor(Color(0x0e, 0x19, 0x1f));
        }
    }

    void render(RenderWindow& window) {
        window.draw(outer);
        window.draw(inner);
    }
};

class Interface {
private:
    Font font;
    
    Text headText;
    Text generationText;
    Text pathFindingText;
    Text startEnd;
    vector<string> generationOptions;
    vector<vector<Text>> generationChoices;
    vector<string> pathOptions;
    vector<vector<Text>> pathChoices;
    pair<int, int> generationSelected;
    pair<int, int> pathSelected;

    Button generate;
    Button resetGenerate;

    SelectButton generateSelect;
    SelectButton findingSelect;

	Maze maze;

    bool generating;
public:
    Interface() {
        generating = false;
        generationOptions = { "DFS", "Prims", "Kruskals", "Wilsons" };
        generationChoices = {
            {Text(), Text()},
            {Text(), Text()}
        };
        pathOptions = { "DFS", "BFS", "Dijkstra", "A Star" };
        pathChoices = {
            {Text(), Text()},
            {Text(), Text()}
        };
        generationSelected = { 0, 0 };
        pathSelected = { 0, 0 };


        // text initialization
        font.loadFromFile("ethnocentric.otf");
        headText.setFont(font);
        headText.setCharacterSize(20);
        headText.setString("Maze Visualizer");
        headText.setPosition(MAZE_WIDTH * TILE_SIZE + 20, 10);

        generationText.setFont(font);
        generationText.setCharacterSize(15);
        generationText.setString("\t\tChoose Maze\nGeneration Algorithm");
        generationText.setPosition(MAZE_WIDTH * TILE_SIZE + 15, 50);

        pathFindingText.setFont(font);
        pathFindingText.setCharacterSize(15);
        pathFindingText.setString("\tChoose Start/End\nAnd Finding Algorithm");
        pathFindingText.setPosition(MAZE_WIDTH * TILE_SIZE + 15, 260);

        startEnd.setFont(font);
        startEnd.setCharacterSize(15);
        startEnd.setString("Start: \t\t  End: ");
        startEnd.setPosition(MAZE_WIDTH * TILE_SIZE + 30, 320);


        // buttons inialization
        generate.setPosition(MAZE_WIDTH * TILE_SIZE + 20, 200);
        generate.setSize(120, 40);
        generate.setCharacterSize(13);
        generate.setText("Generate");
        generate.setFont("ethnocentric.otf"); 
        generate.setNormalColor(Color(150, 150, 150));
        generate.setHoverColor(Color(150, 150, 150));
        generate.setClickedColor(Color(0x04, 0xd9, 0xff));
        generate.setOnClick(generateHandler, ref(maze), ref(generationSelected));

        resetGenerate.setPosition(MAZE_WIDTH * TILE_SIZE + 160, 200);
        resetGenerate.setSize(120, 40);
        resetGenerate.setCharacterSize(13);
        resetGenerate.setText("Reset");
        resetGenerate.setFont("ethnocentric.otf");
        resetGenerate.setNormalColor(Color(150, 150, 150));
        resetGenerate.setHoverColor(Color(150, 150, 150));
        resetGenerate.setClickedColor(Color(0x04, 0xd9, 0xff));
        resetGenerate.setOnClick(resetHandler, ref(maze));

        generateSelect.setPosition(MAZE_WIDTH * TILE_SIZE + 40, 51);
        findingSelect.setPosition(MAZE_WIDTH * TILE_SIZE + 15, 260);
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
                generationChoices[i][j].move(MAZE_WIDTH * TILE_SIZE + 30, 120);

                if (generationSelected.first == i && generationSelected.second == j) {
                    generationChoices[i][j].setFillColor(Color(0x04, 0xd9, 0xff));
                    generationChoices[i][j].setCharacterSize(15);
                    generationChoices[i][j].move(-5, -5);
                }
                window.draw(generationChoices[i][j]);
            }
        }

        if (!generating) {
            // here we will draw the find path text
            window.draw(startEnd);
            window.draw(pathFindingText);

            for (int i = 0; i < pathChoices.size(); i++) {
                for (int j = 0; j < pathChoices[i].size(); j++) {
                    int index = i * pathChoices[0].size() + j;
                    pathChoices[i][j].setFont(font);
                    pathChoices[i][j].setString(pathOptions[index]);
                    pathChoices[i][j].setFillColor(Color::White);
                    pathChoices[i][j].setCharacterSize(13);
                    switch (index) {
                    case 0:
                        pathChoices[i][j].setPosition(30, 0);
                        break;
                    case 1:
                        pathChoices[i][j].setPosition(160, 0);
                        break;
                    case 2:
                        pathChoices[i][j].setPosition(0, pathChoices[i][j].getCharacterSize() + 15);
                        break;
                    case 3:
                        pathChoices[i][j].setPosition(150, pathChoices[i][j].getCharacterSize() + 15);
                        break;
                    }
                    pathChoices[i][j].move(MAZE_WIDTH * TILE_SIZE + 30, 365);

                    if (pathSelected.first == i && pathSelected.second == j) {
                        pathChoices[i][j].setFillColor(Color(0x04, 0xd9, 0xff));
                        pathChoices[i][j].setCharacterSize(15);
                        pathChoices[i][j].move(-5, -5);
                    }
                    window.draw(pathChoices[i][j]);
                }
            }
        }
    }

    void drawButtons(RenderWindow& window) {
        generate.update(window);
        generate.render(window);

        resetGenerate.update(window);
        resetGenerate.render(window);


        // the select buttons logic
        generateSelect.update(window, findingSelect.selected);
        generateSelect.render(window);

        findingSelect.update(window, generateSelect.selected);
        

        if (!generating) {
            // here we will draw the find path options

            findingSelect.render(window);
        }
    }

	void control(RenderWindow& window) {
        //generating = maze.draw(window); // uncomment this line for conditional rendering
        maze.draw(window);

        if (generateSelect.selected) {
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
        }
        else if (findingSelect.selected) {
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if (pathSelected.first > 0) {
                    pathSelected.first--;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                if (pathSelected.first < pathChoices.size() - 1) {
                    pathSelected.first++;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (pathSelected.second > 0) {
                    pathSelected.second--;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (pathSelected.second < pathChoices[0].size() - 1) {
                    pathSelected.second++;
                }
            }
        }
		
        drawButtons(window);
        drawText(window);
	}
};