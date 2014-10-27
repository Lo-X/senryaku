#pragma once

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <map>
#include <string>

#include <Resources.hpp>

class MusicPlayer : private sf::NonCopyable
{
public:
    MusicPlayer();

    void        play(Musics::ID song);
    void        stop();
    void        pause(bool flag = true);
    void        setVolume(float volume);

private:
    sf::Music   mMusic;
    std::map<Musics::ID,std::string>    mFilenames;
    float       mVolume;
};

