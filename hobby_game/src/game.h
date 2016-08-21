#pragma once

#include "keyboard.h"
#include "level.h"
#include "lua.h"
#include "asset_bank.h"
#include "lua_api.h"

namespace hg
{
    class GameImpl;
    class LuaApi;

    class Game
    {
    public:
        Game();
        ~Game();

        /*
            Throws.
        */
        void init(const std::string& exe_dir);

        void clean();

        /*
            Throws.
        */
        void run();

        void quit();

        const AssetBank& get_assets() const { return m_assets; }
        const Keyboard& get_keyboard() const { return m_keyboard; }

        Level& get_level() { return m_level; }
        const Level& get_level() const { return m_level; }

    protected:
        friend class GameImpl;

        void on_key_event(Keycode code, bool state);

    private:
        /*
            Steps one frame.
        */
        void tick(float dt);

        /*
            Renders one frame.
        */
        void render();

    private:
        GameImpl* m_impl;
        bool m_should_quit;

        Lua m_lua;
        AssetBank m_assets;
        Keyboard m_keyboard;

        LuaApi m_lua_api;

        struct
        {
            int start;
            int end;
            int diff;
            float dt;
        } m_frame_time;

        Level m_level;
    };
}