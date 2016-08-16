#pragma once

namespace hg
{
    class Game;
    class Lua;
    class AssetBank;

    class LuaApi
    {
    public:
        LuaApi();

    protected:
        friend class Game;

        void init(Game& game, Lua& lua, AssetBank& assets);

        void destroy();

    private:
        Game* m_game;
        Lua* m_lua;
        AssetBank* m_assets;
    };
}