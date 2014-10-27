#ifndef DATATABLES_H
#define DATATABLES_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>

#include "resources/resourceidentifiers.hpp"

struct ParticleData
{
    sf::Color   color;
    sf::Time    lifetime;
};

// This function inits each particle types with its basic data
std::vector<ParticleData>	initializeParticleData();


#endif // DATATABLES_H
