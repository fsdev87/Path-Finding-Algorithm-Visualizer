#include "Simulator.h"
#include <iostream>




int main() {
	Simulator sim;
	sim.run();


	return 0;
}

//#include <SFML/Graphics.hpp>
//#include <functional>
//
//class Button {
//public:
//    Button() {}
//
//    Button(const sf::Vector2f& size, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor) {
//        buttonShape.setSize(size);
//        buttonShape.setFillColor(idleColor);
//
//        this->idleColor = idleColor;
//        this->hoverColor = hoverColor;
//        this->activeColor = activeColor;
//    }
//
//    void setFont(const sf::Font& font) {
//        buttonText.setFont(font);
//    }
//
//    void setText(const std::string& text) {
//        buttonText.setString(text);
//        centerText();
//    }
//
//    void setTextSize(unsigned int size) {
//        buttonText.setCharacterSize(size);
//        centerText();
//    }
//
//    void setPosition(const sf::Vector2f& position) {
//        buttonShape.setPosition(position);
//        centerText();
//    }
//
//    void setOnClick(const std::function<void()>& onClick) {
//        this->onClick = onClick;
//    }
//
//    template <typename Callable, typename... Args>
//    void setOnClick(Callable&& func, Args&&... args) {
//        onClick = std::bind(std::forward<Callable>(func), std::forward<Args>(args)...);
//    }
//
//    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
//        if (event.type == sf::Event::MouseMoved) {
//            if (buttonShape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                buttonShape.setFillColor(hoverColor);
//            }
//            else {
//                buttonShape.setFillColor(idleColor);
//            }
//        }
//
//        if (event.type == sf::Event::MouseButtonPressed) {
//            if (event.mouseButton.button == sf::Mouse::Left) {
//                if (buttonShape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                    buttonShape.setFillColor(activeColor);
//                }
//            }
//        }
//
//        if (event.type == sf::Event::MouseButtonReleased) {
//            if (event.mouseButton.button == sf::Mouse::Left) {
//                if (buttonShape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                    if (onClick) {
//                        onClick();
//                    }
//                }
//                buttonShape.setFillColor(idleColor);
//            }
//        }
//    }
//
//    void draw(sf::RenderTarget& target) const {
//        target.draw(buttonShape);
//        target.draw(buttonText);
//    }
//
//private:
//    sf::RectangleShape buttonShape;
//    sf::Text buttonText;
//    sf::Color idleColor;
//    sf::Color hoverColor;
//    sf::Color activeColor;
//    std::function<void()> onClick;
//
//    void centerText() {
//        sf::FloatRect textBounds = buttonText.getLocalBounds();
//        sf::FloatRect buttonBounds = buttonShape.getLocalBounds();
//
//        buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
//        buttonText.setPosition(buttonShape.getPosition().x + buttonBounds.width / 2.0f, buttonShape.getPosition().y + buttonBounds.height / 2.0f);
//    }
//};
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//void handleClick(int a, int b) {
//    std::cout << "Button clicked! a + b = " << (a + b) << std::endl;
//}
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Button Example");
//
//    sf::Font font;
//    if (!font.loadFromFile("ethnocentric.otf")) {
//        return -1;
//    }
//
//    Button button(sf::Vector2f(200, 50), sf::Color::Blue, sf::Color::Green, sf::Color::Red);
//    button.setFont(font);
//    button.setText("Click me");
//    button.setTextSize(24);
//    button.setPosition(sf::Vector2f(300, 275));
//    button.setOnClick(handleClick, 5, 3);  // Pass arguments to the callback
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            button.handleEvent(event, window);
//        }
//
//        window.clear();
//        button.draw(window);
//        window.display();
//    }
//
//    return 0;
//}
