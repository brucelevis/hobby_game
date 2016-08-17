#include "game.h"

#include "bitmap.h"
#include "texture.h"
#include "tilemap.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <AL/al.h>
#include <AL/alc.h>

#include "exception.h"

#include <iostream>

#include "lua_script.h"

namespace hg
{
    class GameImpl
    {
    public:
        GameImpl();
        ~GameImpl();

        /*
            Creates the window and the OpenGL context.
            Throws.
        */
        void create(Game& game);

        /*
            Destroys the window and OpenGL context.
        */
        void destroy();

        /*
            Goes through pending events and executes responses to each event.
        */
        void poll_events();

        /*
            Swaps the double buffer on the window to reveal the next frame.
        */
        void swap_window_buffs();

        bool get_should_quit() const { return m_should_quit; }

    private:
        Game* m_game;

        SDL_Window* m_window;
        SDL_GLContext m_gl_context;
        bool m_should_quit;

        ALCdevice* m_al_device;
        ALCcontext* m_al_context;
    };

    GameImpl::GameImpl()
        : m_game()
        , m_window()
        , m_gl_context()
        , m_should_quit()
    {

    }

    GameImpl::~GameImpl()
    {
        
    }

    void GameImpl::create(Game& game)
    {
        m_game = &game;

        SDL_Init(SDL_INIT_EVERYTHING);

        const char* title = "Hobby Game";
        int x = SDL_WINDOWPOS_UNDEFINED;
        int y = SDL_WINDOWPOS_UNDEFINED;
        int w = 1280;
        int h = 720;
        Uint32 flags = SDL_WINDOW_OPENGL;

        m_window = SDL_CreateWindow(title, x, y, w, h, flags);

        if (!m_window)
            throw Exception(std::string("Could not create window. ") + SDL_GetError());

        m_gl_context = SDL_GL_CreateContext(m_window);

        if (!m_gl_context)
            throw Exception(std::string("Could not create OpenGL context. ") + SDL_GetError());

        auto glew_err = glewInit();
        if (glew_err)
            throw Exception("Could not initialize GLEW. Error code: " + std::to_string(glew_err));

        m_al_device = alcOpenDevice(nullptr);
        if (m_al_device)
        {
            m_al_context = alcCreateContext(m_al_device, nullptr);
            if (m_al_context)
            {
                alcMakeContextCurrent(m_al_context);
            }
            else
            {
                throw Exception("Could not create OpenAL context.");
            }
        }
        else
        {
            throw Exception("Could not create OpenAL device.");
        }
    }

    void GameImpl::destroy()
    {
        alcDestroyContext(m_al_context);
        m_al_context = nullptr;

        alcCloseDevice(m_al_device);
        m_al_device = nullptr;

        SDL_GL_DeleteContext(m_gl_context);
        m_gl_context = nullptr;

        SDL_DestroyWindow(m_window);
        m_window = nullptr;

        SDL_Quit();
    }

    static Keycode conv_scancode_to_keycode(SDL_Scancode sc)
    {
        switch (sc)
        {
        case SDL_SCANCODE_UP:
            return Keycode::up;
        case SDL_SCANCODE_DOWN:
            return Keycode::down;
        case SDL_SCANCODE_LEFT:
            return Keycode::left;
        case SDL_SCANCODE_RIGHT:
            return Keycode::right;

        case SDL_SCANCODE_ESCAPE:
            return Keycode::escape;

        default:
            return Keycode::none;
        }
    }

    void GameImpl::poll_events()
    {
        SDL_Event e;
        Keycode kc;

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                m_should_quit = true;
                break;

            case SDL_KEYDOWN:
                kc = conv_scancode_to_keycode(e.key.keysym.scancode);
                m_game->on_key_event(kc, true);
                break;

            case SDL_KEYUP:
                kc = conv_scancode_to_keycode(e.key.keysym.scancode);
                m_game->on_key_event(kc, false);
                break;
            }
        }
    }

    void GameImpl::swap_window_buffs()
    {
        SDL_GL_SwapWindow(m_window);
    }

    Game::Game()
        : m_impl(new GameImpl())
        , m_frame_time()
        , m_should_quit()
    {

    }

    Game::~Game()
    {
        delete m_impl;
    }

    void Game::init(const std::string& exe_dir)
    {
        m_impl->create(*this);

        m_lua.init(exe_dir);
        m_assets.init(m_lua);
        m_lua_api.init(*this, m_lua, m_assets);

        auto main_script_id = m_lua.load_script("assets/main.lua");
        auto main_script = m_lua.get_script(main_script_id);
        main_script->run();

        glMatrixMode(GL_PROJECTION);
        glOrtho(0.0, 1280.0, 720.0, 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_level.init(*this);
    }

    void Game::clean()
    {
        m_lua_api.destroy();

        m_assets.destroy();
        m_lua.destroy();

        m_impl->destroy();
    }

    void Game::run()
    {
        bool running = true;

        m_frame_time.dt = 1.0f / 60.0f;
        while (running)
        {
            m_frame_time.start = (int)SDL_GetTicks();

            m_impl->poll_events();
            running = !m_impl->get_should_quit();

            tick(m_frame_time.dt);
            render();

            m_keyboard.clear_key_diffs();

            m_frame_time.end = (int)SDL_GetTicks();
            m_frame_time.diff = m_frame_time.end - m_frame_time.start;

            static const float MS_TO_S = 1.0f / 1000.0f;
            m_frame_time.dt = (float)(m_frame_time.diff * MS_TO_S);

            if (m_should_quit)
                break;
        }
    }

    void Game::quit()
    {
        m_should_quit = true;
    }

    void Game::on_key_event(Keycode code, bool state)
    {
        m_keyboard.on_key_change(code, state);
    }

    void Game::tick(float dt)
    {
        m_level.tick(dt);

        if (m_keyboard.was_key_pressed(Keycode::escape))
        {
            quit();
        }
    }

    void Game::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        /*
        auto& tmap = m_level.get_tilemap();
        
        float su = 1.0f / tmap.get_texture().get_width();
        float sv = 1.0f / tmap.get_texture().get_height();

        glEnable(GL_TEXTURE_2D);
        
        glBegin(GL_QUADS);

        for (int i = 0; i < tmap.get_num_tiles(); ++i)
        {
            TileInfo ti;
            tmap.get_tile_info(i, ti);

            if (ti.id >= 0)
            {
                vcm::vec4 uv_rect = 
                    vcm::vec4((float)ti.clip_x, (float)ti.clip_y, (float)ti.clip_w, (float)ti.clip_h) 
                    * vcm::vec4(su, sv, su, sv);

                uv_rect += vcm::vec4(0.0f, 0.0f, uv_rect.x, uv_rect.y);

                glTexCoord2f(uv_rect.x, uv_rect.y);
                glVertex2f((float)ti.x, (float)ti.y);
                glTexCoord2f(uv_rect.x, uv_rect.w);
                glVertex2f((float)ti.x, (float)ti.y + ti.h);
                glTexCoord2f(uv_rect.z, uv_rect.w);
                glVertex2f((float)ti.x + ti.w, (float)ti.y + ti.h);
                glTexCoord2f(uv_rect.z, uv_rect.y);
                glVertex2f((float)ti.x + ti.w, (float)ti.y);
            }
        }

        glEnd();

        glDisable(GL_TEXTURE_2D);

        auto& pos = m_level.get_player().get_position();

        int w = 32, h = 32;
        
        glBegin(GL_QUADS);

        glVertex2f(std::floor(pos.x), std::floor(pos.y));
        glVertex2f(std::floor(pos.x), std::floor(pos.y) + h);
        glVertex2f(std::floor(pos.x) + w, std::floor(pos.y) + h);
        glVertex2f(std::floor(pos.x) + w, std::floor(pos.y));

        glEnd();

        */

        m_impl->swap_window_buffs();
    }
}