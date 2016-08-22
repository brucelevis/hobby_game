#include "lua_object.h"

#include "exception.h"

#include "lua.h"

#include <lua.hpp>

namespace hg
{
    LuaObject::LuaObject()
        : m_lua()
        , m_object_ref(LUA_NOREF)
    {

    }

    LuaObject::LuaObject(Lua& lua, int object_ref)
        : LuaObject()
    {
        create(&lua, object_ref);
    }

    LuaObject::LuaObject(const LuaObject& o)
        : LuaObject()
    {
        *this = o;
    }

    LuaObject::LuaObject(LuaObject&& o)
        : LuaObject()
    {
        *this = std::move(o);
    }

    LuaObject::~LuaObject()
    {
        destroy();
    }

    void LuaObject::create(Lua* lua, int object_ref)
    {
        destroy();

        if (lua)
        {
            auto L = (lua_State*)lua->get_L();

            m_lua = lua;
            lua_rawgeti(L, LUA_REGISTRYINDEX, object_ref);
            m_object_ref = luaL_ref(L, LUA_REGISTRYINDEX);
        }
        else
        {
            m_lua = nullptr;
            m_object_ref = LUA_NOREF;
        }
    }

    void LuaObject::destroy()
    {
        if (m_lua)
        {
            auto L = (lua_State*)m_lua->get_L();
            luaL_unref(L, LUA_REGISTRYINDEX, m_object_ref);
            m_object_ref = LUA_NOREF;
            m_lua = nullptr;
        }
    }

    void LuaObject::check_basics() const
    {
        if (!m_lua)
            throw Exception("Tried to use a LuaObject with no lua.");
        if (m_object_ref == LUA_NOREF)
            throw Exception("Tried to use a LuaObject that has no object_ref.");
        if (m_object_ref == LUA_REFNIL)
            throw Exception("Tried to use a nil LuaObject.");
    }

    LuaObject& LuaObject::operator=(const LuaObject& o)
    {
        create(o.m_lua, o.m_object_ref);

        return *this;
    }

    LuaObject& LuaObject::operator=(LuaObject&& o)
    {
        m_lua = o.m_lua;
        m_object_ref = o.m_object_ref;

        o.m_lua = nullptr;
        o.m_object_ref = LUA_NOREF;

        return *this;
    }
}