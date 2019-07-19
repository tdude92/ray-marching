#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "raymarching.hpp"

#define toRadians(n) (n * M_PI/180)
#define toDegrees(n) (n * 180/M_PI)

const int screenWidth = 1920;
const int screenHeight = 1080;

void march(sf::Vector2f lightSource, sf::VertexArray &pts, sf::VertexArray &illumination, std::vector<sf::CircleShape> &circles) {
    sf::Vector2f currentRayPos;
    double distToClosestShape;
    
    double raySlopeX, raySlopeY;
    for (int i = 0; i < 1440; ++i) {
        currentRayPos = lightSource;
        distToClosestShape = getDistToClosestCircle(currentRayPos, circles);

        raySlopeX = cos(toRadians(i) / 4);
        raySlopeY = sin(toRadians(i) / 4);
        while (currentRayPos.x >= 0 && currentRayPos.x <= screenWidth && currentRayPos.y >= 0 && currentRayPos.y <= screenHeight) {
            currentRayPos.x += raySlopeX * distToClosestShape;
            currentRayPos.y += raySlopeY * distToClosestShape;
            distToClosestShape = getDistToClosestCircle(currentRayPos, circles);

            if (distToClosestShape <= 1) {
                illumination.append(sf::Vertex(currentRayPos, sf::Color::Red));
                break;
            }
        }
        pts[i * 2] = sf::Vertex(lightSource, sf::Color::White);
        pts[i * 2 + 1] = sf::Vertex(currentRayPos, sf::Color::White);
    }
}

int main() {
    srand(time(NULL));

    sf::RenderWindow root(sf::VideoMode(screenWidth, screenHeight), "Ray Marching", sf::Style::Fullscreen);
    root.setMouseCursorVisible(false);

    std::vector<sf::CircleShape> circles;
    for (int i = 0; i < 12; ++i) {
        circles.push_back(sf::CircleShape(rand() % 25 + 75));
        sf::CircleShape &circle = circles[circles.size() - 1];

        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setFillColor(sf::Color(0, 0, 0));
        circle.setPosition(rand() % screenWidth, rand() % screenHeight);
    }
    
    // Ray marching.
    sf::VertexArray pts(sf::Lines, 2880);
    sf::VertexArray illumination(sf::Points);
    sf::Vector2f lightSource(640, 360);
    march(lightSource, pts, illumination, circles);

    sf::Mouse::setPosition(sf::Vector2i(lightSource.x, lightSource.y));
    sf::Vector2i prevPos = sf::Mouse::getPosition();
    while (root.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            root.close();
        }

        if (sf::Mouse::getPosition() != prevPos) {
            prevPos = sf::Mouse::getPosition();
            lightSource = sf::Vector2f(prevPos.x, prevPos.y);
            illumination.clear();
            march(lightSource, pts, illumination, circles);
        }

        root.clear();
        for (unsigned int i = 0; i < circles.size(); ++i) {
            root.draw(circles[i]);
        }
        root.draw(pts);
        root.draw(illumination);
        root.display();
    }

    return 0;
}