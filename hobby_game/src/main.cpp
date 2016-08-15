#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "exception.h"

#include <iostream>

int main(int argc, char** argv)
{
    using namespace hg;

    Game g;

    try
    {
        g.init();
        g.run();
    }
    catch (const Exception& e)
    {
        g.clean();

        std::cout << e.what() << std::endl;
        std::getchar();
    }

    return 0;
}