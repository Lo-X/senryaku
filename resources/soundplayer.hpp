#pragma once

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <list>

#include <Resources.hpp>

class SoundPlayer : private sf::NonCopyable
{
public:
    SoundPlayer();

    void            play(Sounds::ID sound);
    void            play(Sounds::ID sound, sf::Vector2f position);

    void            removeStoppedSounds();
    void            setListenerPosition(sf::Vector2f position);
    sf::Vector2f    getListenerPosition() const;

private:
    SoundHolder             mSoundBuffers;
    std::list<sf::Sound>    mSounds;
};
