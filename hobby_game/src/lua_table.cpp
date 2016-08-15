#include "lua_table.h"
#include "lua_value.h"
#include "lua.h"

#include <lua.hpp>

#include "exception.h"

#include <iostream>

namespace hg
{
    LuaTable::LuaTable()
        : m_lua()
        , m_table_ref(LUA_NOREF)
    {

    }

    LuaTable::LuaTable(Lua& lua, int table_ref)
        : LuaTable()
    {
        create(&lua, table_ref);
    }

    LuaTable::LuaTable(const LuaTable& t)
        : LuaTable()
    {
        *this = t;
    }

    LuaTable::LuaTable(LuaTable&& t)
        : LuaTable()
    {
        *this = std::move(t);
    }

    LuaTable::~LuaTable()
    {
        destroy();
    }

    void LuaTable::create(Lua* lua, int table_ref)
    {
        destroy();

        if (lua)
        {
            auto L = (lua_State*)lua->get_L();

            m_lua = lua;
            lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);
            m_table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
        }
        else
        {
            m_lua = nullptr;
            m_table_ref = LUA_NOREF;
        }
    }

    void LuaTable::destroy()
    {
        if (m_lua)
        {
            auto L = (lua_State*)m_lua->get_L();
            luaL_unref(L, LUA_REGISTRYINDEX, m_table_ref);
            m_table_ref = LUA_NOREF;
            m_lua = nullptr;
        }
    }

    void LuaTable::check_basics() const
    {
        if (!m_lua)
            throw Exception("Tried to get_value() from a LuaTable with no lua.");
        if (m_table_ref == LUA_NOREF)
            throw Exception("Tried to use a LuaTable that has no table_ref.");
        if (m_table_ref == LUA_REFNIL)
            throw Exception("Tried to use a nil LuaTable.");
    }

    bool LuaTable::get_value(LuaType out_type, const LuaValue& key, LuaValue& out_value) const
    {
        check_basics();

        auto L = (lua_State*)m_lua->get_L();

        lua_rawgeti(L, LUA_REGISTRYINDEX, m_table_ref);

        switch (key.get_type())
        {
        case LuaType::_int:
            lua_pushinteger(L, key.get_int());
            break;
        case LuaType::_double:
            lua_pushnumber(L, key.get_double());
            break;
        case LuaType::string:
            lua_pushstring(L, key.get_string().c_str());
            break;
        case LuaType::table:
            lua_rawgeti(L, LUA_REGISTRYINDEX, key.get_table().get_ref());
            break;
        default:
            throw Exception("Bad LuaValue for key in get_value().");
        }

        lua_gettable(L, -2);

        if (lua_isnil(L, -1))
        {
            out_value = LuaValue();
            return false;
        }

        Exception bad_conversion("Tried to LuaTable::get_value with bad out_type");
        
        int out_table_ref;
        switch (out_type)
        {
        case LuaType::_int:
            if (lua_isinteger(L, -1))
                out_value = (int)lua_tointeger(L, -1);
            else
                throw bad_conversion;
            break;
        case LuaType::_double:
            if (lua_isnumber(L, -1))
                out_value = lua_tonumber(L, -1);
            else
                throw bad_conversion;
            break;
        case LuaType::string:
            if (lua_isstring(L, -1))
                out_value = lua_tostring(L, -1);
            else
                throw bad_conversion;
            break;
        case LuaType::table:
            if (lua_istable(L, -1))
            {
                out_table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
                out_value = LuaTable(*m_lua, out_table_ref);
                luaL_unref(L, LUA_REGISTRYINDEX, out_table_ref);
            }
            else
            {
                throw bad_conversion;
            }
            break;
        default:
            throw Exception("Bad LuaValue for out_type in get_value().");
        }

        return true;
    }

    void LuaTable::to_array(std::vector<LuaValue>& out_array) const
    {
        check_basics();

        auto L = (lua_State*)m_lua->get_L();

        lua_rawgeti(L, LUA_REGISTRYINDEX, m_table_ref);
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

    LuaTable& LuaTable::operator=(const LuaTable& t)
    {
        create(t.m_lua, t.m_table_ref);

        return *this;
    }

    LuaTable& LuaTable::operator=(LuaTable&& t)
    {
        m_lua = t.m_lua;
        m_table_ref = t.m_table_ref;

        t.m_lua = nullptr;
        t.m_table_ref = LUA_NOREF;

        return *this;
    }
}