#include <application/application.hpp>
#include <iostream>

int main()
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

    return 0;
}

