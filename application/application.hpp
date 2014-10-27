#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <Resources.hpp>
#include <Controllers.hpp>
#include <States.hpp>

class Application
{
public:
    Application(unsigned int width, unsigned int height, const std::string& title);

    void    run();
    void    stop();

private:
    void    processEvents();
    void    update(sf::Time dt);
    void    render();

    void    registerStates();
    void    updateStatistics(sf::Time dt);

private:
    static const sf::Time   sTimePerFrame;
    // Context
    sf::RenderWindow        mWindow;
    TextureHolder           mTextures;
    FontHolder              mFonts;
    SoundPlayer             mSounds;
    MusicPlayer             mMusic;
    ScriptPlayer            mScripts;
    PlayerController        mPlayer;
    // OpponentController

    StateStack              mStateStack;

    // Statistics
    sf::Text                mStatisticsText;
    sf::Time                mStatisticsUpdateTime;
    std::size_t             mStatisticsNumFrames;
};

