#include "lua_table.h"
#include "lua_value.h"
#include "lua.h"

#include <lua.hpp>

#include "exception.h"

#include <iostream>

namespace hg
{
    LuaTable::LuaTable()
        : LuaObject()
    {

    }

    void LuaTable::create(Lua& lua)
    {
        auto L = (lua_State*)lua.get_L();

        lua_newtable(L);
        int t = luaL_ref(L, LUA_REGISTRYINDEX);

        LuaObject::create(&lua, t);

        luaL_unref(L, LUA_REGISTRYINDEX, t);
    }

    bool LuaTable::get_value(LuaType out_type, const LuaValue& key, LuaValue& out_value) const
    {
        check_basics();

        auto L = (lua_State*)m_lua->get_L();

        lua_rawgeti(L, LUA_REGISTRYINDEX, m_object_ref);

        key.push(*m_lua);

        lua_gettable(L, -2);

        if (lua_isnil(L, -1))
        {
            out_value = LuaValue();
            return false;
        }

        out_value.pull(*m_lua, -1, out_type);

        return true;
    }

    void LuaTable::set_value(const std::string& name, const LuaValue& value)
    {
        check_basics();

        auto L = (lua_State*)m_lua->get_L();

        lua_rawgeti(L, LUA_REGISTRYINDEX, m_object_ref);

        auto key = LuaValue(name);
        key.push(*m_lua);
        value.push(*m_lua);

        lua_settable(L, -3);

        lua_pop(L, 1);
    }

    void LuaTable::to_array(std::vector<LuaValue>& out_array) const
    {
        check_basics();

        auto L = (lua_State*)m_lua->get_L();

        lua_rawgeti(L, LUA_REGISTRYINDEX, m_object_ref);
        int t = lua_gettop(L);

        lua_pushnil(L);
        while (lua_next(L, t) != 0)
        {
            auto value = m_lua->get_value(-1);
            if (value.get_type() != LuaType::undefined)
                out_array.push_back(value);

            lua_pop(L, 1);
        }
    }
}