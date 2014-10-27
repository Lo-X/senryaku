#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include "resources/animation.hpp"

// Helpers to set the origin of sprites/text/... at center
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(Animation& animation);

#endif // UTILS_H
