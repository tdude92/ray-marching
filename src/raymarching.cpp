#include <SFML/Graphics.hpp>
#include <cmath>
#include "raymarching.hpp"

double distance2P(sf::Vector2f p1, sf::Vector2f p2) {
    // find the distance between two points.
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Signed distance functions.
double signedDistToCircle(sf::Vector2f point, sf::Vector2f circleCenter, double radius) {
    // Find the distance between a point and a circle.
    return distance2P(point, circleCenter) - radius;
}

// Get closest shape.
double getDistToClosestCircle(const sf::Vector2f currentRayPos, const std::vector<sf::CircleShape> &circles) {
    // Get the distance to the closest circle.
    double distToClosestCircle;
    std::vector<double> signedDistances;
    for (unsigned int i = 0; i < circles.size(); ++i) {
        signedDistances.push_back(signedDistToCircle(currentRayPos, circles[i].getPosition(), circles[i].getRadius()));
    }

    distToClosestCircle = signedDistances[0];
    for (unsigned int i = 1; i < signedDistances.size(); ++i) {
        if (signedDistances[i] < distToClosestCircle) {
            distToClosestCircle = signedDistances[i];
        }
    }

    return distToClosestCircle;
}
    