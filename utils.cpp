#include <utils.hpp>

void centerOrigin(sf::Sprite &sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(Animation& animation)
{
    sf::FloatRect bounds = animation.getLocalBounds();
    animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}
