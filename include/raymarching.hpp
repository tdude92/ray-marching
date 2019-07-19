#ifndef RAYMARCHING_H
#define RAYMARCHING_H

#include <SFML/Graphics.hpp>

double distance2P(sf::Vector2f p1, sf::Vector2f p2);

// Signed distance functions.
double signedDistToCircle(sf::Vector2f point, sf::Vector2f circleCenter, double radius);

// Functions that find the distance to the closest shape.
double getDistToClosestCircle(const sf::Vector2f currentRayPos, const std::vector<sf::CircleShape> &circles);

#endif