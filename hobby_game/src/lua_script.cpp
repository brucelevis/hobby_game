#include "lua_script.h"
#include "lua.h"

#include <lua.hpp>

#include "exception.h"
#include "lua_table.h"

namespace hg
{
    LuaScript::LuaScript()
        : m_id()
        , m_lua()
        , m_script_ref(LUA_NOREF)
    {

    }

    LuaScript::LuaScript(Lua& lua, int script_ref)
        : m_id()
        , m_lua(&lua)
        , m_script_ref(script_ref)
    {

    }

    void LuaScript::run()
    {
        if (!m_script_ref)
            throw Exception("Tried to run a nonexistant script.");

        auto L = (lua_State*)m_lua->get_L();
        lua_rawgeti(L, LUA_REGISTRYINDEX, m_script_ref);

        int result = lua_pcall(L, 0, LUA_MULTRET, 0);
        if (result != LUA_OK)
            Lua::throw_lua_err(L);
    }

    void LuaScript::run(std::vector<LuaValue>& out_returns)
    {
        auto L = (lua_State*)m_lua->get_L();

        int start_top = lua_gettop(L);

        run();

        int num_result = lua_gettop(L) - start_top;
        if (num_result)
        {
            for (int i = 0; i < num_result; ++i)
            {
                auto value = m_lua->get_value(-i - 1);
                out_returns.push_back(value);
            }
        }
    }
}