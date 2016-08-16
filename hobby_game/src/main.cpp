#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "exception.h"

#include <iostream>

#include "util.h"

int main(int argc, char** argv)
{
    using namespace hg;

    Game g;

    const char* exe_name = argv[0];
    std::vector<std::string> exe_name_split;
    split_string(exe_name, "\\", 1, exe_name_split);
    std::string exe_dir;

    for (int i = 0; i < exe_name_split.size() - 1; ++i)
    {
        exe_dir.append(exe_name_split[i] + "/");
    }

    try
    {
        g.init(exe_dir);
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