#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

class Ball {
    public:
        Ball(float radius) {
            shape.setRadius(radius);
            shape.setFillColor(sf::Color(rand() % 256,rand() % 256,rand() % 256));
        }

        void setPosition(sf::Vector2f pos){
            shape.setPosition(pos);
        }

        bool isMouseOver(sf::RenderWindow& window){
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            sf::Vector2f shapePos = shape.getPosition();

            float dist = sqrt(pow(mousePos.x - shapePos.x,2) + pow(mousePos.y - shapePos.y,2) * 1.0);

            if (dist <= shape.getRadius() * 2)
            {
                return true;
            }
            return false;
        }

        void update(float deltaTime,float mouseVelocity) {
            std::cout << "Inital Velocity: x " << velocity.x << " y:" << velocity.y << "\n";
            velocity.x += mouseVelocity * deltaTime; // Apply mouse velocity in x 
            velocity.y += gravity * deltaTime; // Apply gravity
            velocity.y += mouseVelocity * deltaTime; // Apply mouse velocity in y
            shape.move(velocity.x * deltaTime,velocity.y * deltaTime); // Updates Pos
            std::cout << "Updated Velocity: x " << velocity.x << " y:" << velocity.y << "\n";

            // Checks collision
            // Bottom
            if (shape.getPosition().y + shape.getRadius() * 2 > sf::VideoMode::getDesktopMode().height)
            {
                shape.setPosition(shape.getPosition().x,sf::VideoMode::getDesktopMode().height - shape.getRadius() * 2);
                velocity.y = -velocity.y * 0.8f; // Reverse velocity
                velocity.x *= 0.95f; // Apply friction
            } else if (shape.getPosition().y <= 0) // Top 
            {
                shape.setPosition(shape.getPosition().x,0 + shape.getRadius() * 2);
                velocity.y = -velocity.y * 0.8f; // Reverse velocity
                velocity.x *= 0.95f; // Apply friction
            } else if (shape.getPosition().x <= 0 ){
                shape.setPosition(0 + shape.getRadius() * 2,shape.getPosition().y);
                velocity.x = -velocity.y * 0.8f; // Reverse velocity
                velocity.y *= 0.95f; // Apply friction
            } else if ((shape.getPosition().x + shape.getRadius() * 2 > sf::VideoMode::getDesktopMode().width))
            {
                shape.setPosition(sf::VideoMode::getDesktopMode().width - shape.getRadius() * 2,shape.getPosition().y);
                velocity.x = -velocity.x * 0.8f; // Reverse velocity
                velocity.y *= 0.95f; // Apply friction
            }
        }

        void draw(sf::RenderWindow& window) {
            window.draw(shape);
        }

    private:
        sf::CircleShape shape;
        sf::Vector2f velocity;
        const float gravity = 9.81f; // Gravity constant
};