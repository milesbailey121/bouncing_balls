#include <SFML/Graphics.hpp>
#include <iostream>
#include <ball.cpp>

int main() {
    // Create Window and cap framerate
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Bouncing Balls");

    // Ball
    Ball ball(50);

    // Physics
    float deltaTime = 0.002f;
    sf::Vector2f initalMousePos;
    float mouseVelocity;
    bool lockPhysics = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        lockPhysics = true;
                        initalMousePos = sf::Vector2f(sf::Mouse::getPosition(window));
                    }
                    
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        lockPhysics = false;
                    }
                default:
                    break;
            }
        }


        if (ball.isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            ball.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        }
    
        if (lockPhysics == false)
        {
            sf::Vector2f currentMousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            //Distance calc
            mouseVelocity = sqrt(pow(initalMousePos.x - currentMousePos.x,2) + pow(initalMousePos.y - currentMousePos.y,2) * 1.0);

            mouseVelocity = mouseVelocity * 0.001;

            ball.update(deltaTime,mouseVelocity);
        }
    
        window.clear();
        
        ball.draw(window);

        window.display();
    }

    return 0;
}
