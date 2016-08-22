#include "lua_function.h"

#include "lua.h"
#include "lua_value.h"

#include <lua.hpp>

namespace hg
{
    LuaFunction::LuaFunction()
        : LuaObject()
    {

    }

    void LuaFunction::call(const LuaValue* params, int num_params, std::vector<LuaValue>& out_results)
    {
        check_basics();

        auto L = (lua_State*)m_lua->get_L();

        int top = lua_gettop(L);

        lua_rawgeti(L, LUA_REGISTRYINDEX, m_object_ref);

        for (int i = 0; i < num_params; ++i)
        {
            params[i].push(*m_lua);
        }

        int err = lua_pcall(L, num_params, LUA_MULTRET, 0);

        int num_results = lua_gettop(L) - top;

        for (int i = 0; i < num_results; ++i)
        {
            LuaValue value;
            value.pull(*m_lua, top + i + 1, LuaType::undefined);
            out_results.push_back(value);
        }

        if(err)
            m_lua->throw_lua_err(L);
    }
}