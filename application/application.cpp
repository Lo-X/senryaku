#include "application.hpp"
#include <SFML/Window/Event.hpp>

const sf::Time Application::sTimePerFrame = sf::seconds(1.f/60.f);

Application::Application(unsigned int width, unsigned int height, const std::string &title) :
    mWindow(sf::VideoMode(width, height), title.c_str(), sf::Style::Close),
    // Context
    mStatisticsText(),
    mStatisticsUpdateTime(),
    mStatisticsNumFrames(0)
{
    mWindow.setKeyRepeatEnabled(false);

    // Resources
    //mFonts.load(Fonts::Main, "assets/fonts/sansation.ttf");
    //mTextures.load(Textures::Particle, "assets/textures/particle.png");
    //mScripts.registerFile(Scripts::HelloWorld, "assets/scripts/helloworld.lua");

    //mStatisticsText.setFont(mFonts.get(Fonts::Main));
    mStatisticsText.setColor(sf::Color::White);
    mStatisticsText.setPosition(5.f,5.f);
    mStatisticsText.setCharacterSize(10);

    registerStates();
    //mStateStack.pushState(States::Title);
}


void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while(timeSinceLastUpdate > sTimePerFrame)
        {
            timeSinceLastUpdate -= sTimePerFrame;

            processEvents();
            update(sTimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
            //if (mStateStack.isEmpty())
                //mWindow.close();
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Application::stop()
{
    mWindow.close();
}

void Application::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        //mStateStack.handleEvent(event);
        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    //mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    //mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Application::registerStates()
{
    //mStateStack.registerState<TitleState>(States::Title);
    /*mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<LoadingState>(States::Loading);
    mStateStack.registerState<GameOverState>(States::GameOver);*/
}

void Application::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if(mStatisticsUpdateTime >= sf::seconds(1.f))
    {
        mStatisticsText.setString(
                    "Frames/sec = " + std::to_string(mStatisticsNumFrames) + "\n" +
                    "Time/update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us"
        );

        mStatisticsNumFrames = 0;
        mStatisticsUpdateTime -= sf::seconds(1.f);
    }
}
