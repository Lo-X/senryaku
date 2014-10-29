#include <application/application.hpp>
#include <network/gameserver.hpp>
#include <bandit/bandit.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc >= 2)
    {
        if(std::string(argv[1]) == "-s")
        {
            std::cout << "Starting Senryaku server" << std::endl;
            try
            {
                GameServer server;
                server.run();
            }
            catch(std::exception& e)
            {
                std::cerr << std::endl << "Senryaku server crashed on exception: " << e.what() << std::endl;
            }
        }
        else if(std::string(argv[1]) == "-test")
        {
            return bandit::run(argc, argv);
        }
    }
    else
    {
        try
        {
            Application app(1024, 768, "Senryaku");
            app.run();
        }
        catch(std::exception& e)
        {
            std::cerr << std::endl << "Senryaku crashed on exception: " << e.what() << std::endl;
        }
    }

    return 0;
}

