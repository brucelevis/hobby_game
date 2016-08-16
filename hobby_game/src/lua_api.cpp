#include "lua_api.h"

#include "lua.h"
#include "lua_value.h"
#include "lua_script.h"

#include "exception.h"

#include "game.h"

#include <lua.hpp>

namespace hg
{
    static AssetBank* asset_bank = nullptr;

    LuaApi::LuaApi()
        : m_game()
    {

    }

    static int LUA_load_asset(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 2)
        {
            throw Exception("LUA_load_asset: bad number of arguments");
        }

        int asset_type = lua_tointeger(L, 1);
        std::string asset_file_name = lua_tostring(L, 2);

        int asset_id = asset_bank->load_asset((AssetType)asset_type, asset_file_name);

        lua_pushinteger(L, asset_id);
        return 1;
    }

    static luaL_Reg lua_functions[] =
    {
        { "load_asset", &LUA_load_asset }
    };

    void LuaApi::init(Game& game, Lua& lua, AssetBank& assets)
    {
        m_game = &game;

        asset_bank = &assets;

        auto L = (lua_State*)lua.get_L();

        lua_newtable(L);
        
        for (const auto& reg : lua_functions)
        {
            lua_pushstring(L, reg.name);
            lua_pushcfunction(L, reg.func);
            lua_rawset(L, -3);
        }

        lua_setglobal(L, "api");
    }

    void LuaApi::destroy()
    {

    }
}