#include "lua_value.h"

#include "lua.h"
#include "exception.h"
#include "lua_table.h"

#include <lua.hpp>

namespace hg
{
    LuaValue::LuaValue()
        : m_type(LuaType::undefined)
    {

    }

    LuaValue::LuaValue(int i)
        : m_type(LuaType::_int)
    {
        m_number.as_int = i;
    }

    LuaValue::LuaValue(float f)
        : m_type(LuaType::_double)
    {
        m_number.as_double = (double)f;
    }

    LuaValue::LuaValue(double d)
        : m_type(LuaType::_double)
    {
        m_number.as_double = d;
    }

    LuaValue::LuaValue(const char* cs)
        : m_type(LuaType::string)
        , m_string(cs)
    {

    }

    LuaValue::LuaValue(const std::string& s)
        : m_type(LuaType::string)
        , m_string(s)
    {

    }

    LuaValue::LuaValue(const LuaTable& t)
        : m_type(LuaType::table)
        , m_table(t)
    {

    }

    LuaValue::LuaValue(const LuaFunction& f)
        : m_type(LuaType::function)
        , m_function(f)
    {

    }

    void LuaValue::push(Lua& lua) const
    {
        auto L = (lua_State*)lua.get_L();
        switch (get_type())
        {
        case LuaType::_int:
            lua_pushinteger(L, get_int());
            break;
        case LuaType::_double:
            lua_pushnumber(L, get_double());
            break;
        case LuaType::string:
            lua_pushstring(L, get_string().c_str());
            break;
        case LuaType::table:
            lua_rawgeti(L, LUA_REGISTRYINDEX, get_table().get_ref());
            break;
        case LuaType::function:
            lua_rawgeti(L, LUA_REGISTRYINDEX, get_function().get_ref());
            break;
        default:
            throw Exception("Bad LuaValue for LuaValue::push().");
        }
    }

    void LuaValue::pull(const Lua& lua, int idx, LuaType type)
    {
        auto L = (lua_State*)lua.get_L();

        Exception bad_conversion("Tried to LuaValue::pull with bad type parameter");

        int object_ref;
        LuaTable table;
        LuaFunction function;

        if (type == LuaType::undefined)
        {
            switch (lua_type(L, idx))
            {
            case LUA_TNUMBER:
                if (lua_isinteger(L, idx))
                    type = LuaType::_int;
                else if (lua_isnumber(L, idx))
                    type = LuaType::_double;
                break;
            case LUA_TSTRING:
                type = LuaType::string;
                break;
            case LUA_TTABLE:
                type = LuaType::table;
                break;
            case LUA_TFUNCTION:
                type = LuaType::function;
                break;
            }
        }

        switch (type)
        {
        case LuaType::_int:
            if (lua_isinteger(L, idx))
                *this = (int)lua_tointeger(L, idx);
            else
                throw bad_conversion;
            break;
        case LuaType::_double:
            if (lua_isnumber(L, idx))
                *this = lua_tonumber(L, idx);
            else
                throw bad_conversion;
            break;
        case LuaType::string:
            if (lua_isstring(L, idx))
                *this = std::string(lua_tostring(L, idx));
            else
                throw bad_conversion;
            break;
        case LuaType::table:
            if (lua_istable(L, idx))
            {
                lua_pushvalue(L, idx);
                object_ref = luaL_ref(L, LUA_REGISTRYINDEX);
                table.create((Lua*)&lua, object_ref);
                *this = table;
                luaL_unref(L, LUA_REGISTRYINDEX, object_ref);
            }
            else
            {
                throw bad_conversion;
            }
            break;
        case LuaType::function:
            if (lua_isfunction(L, idx))
            {
                lua_pushvalue(L, idx);
                object_ref = luaL_ref(L, LUA_REGISTRYINDEX);
                function.create((Lua*)&lua, object_ref);
                *this = function;
                luaL_unref(L, LUA_REGISTRYINDEX, object_ref);
            }
            else
            {
                throw bad_conversion;
            }
            break;
        default:
            throw Exception("Bad LuaType for type in LuaValue::pull().");
        }
    }
}