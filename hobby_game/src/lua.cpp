#include "lua.h"
#include "exception.h"

#include "lua_value.h"
#include "lua_table.h"
#include "lua_script.h"

#include <lua.hpp>

#include <string>
#include <iostream>

namespace hg
{
    void Lua::throw_lua_err(void* L_)
    {
        auto L = (lua_State*)L_;

        Exception err(lua_tostring(L, -1));
        lua_pop(L, 1);
        throw err;
    }

    Lua::Lua()
        : m_L()
        , m_next_script_id(1)
    {

    }

    Lua::~Lua()
    {
        
    }

    void Lua::init()
    {
        m_L = luaL_newstate();
        auto L = (lua_State*)m_L;

        luaL_openlibs(L);

        /*
        //load file
        int result = luaL_loadfile(L, "assets/tilemap.lua");
        if (result != LUA_OK)
            throw_lua_err(L);

        //store file
        int file_chunk = luaL_ref(L, LUA_REGISTRYINDEX);

        //run file
        lua_rawgeti(L, LUA_REGISTRYINDEX, file_chunk);
        result = lua_pcall(L, 0, LUA_MULTRET, 0);
        if (result != LUA_OK)
            throw_lua_err(L);
        */

        /*
        int script_id = load_script("assets/tilemap.lua");
        auto script = get_script(script_id);
        script->run();

        Exception bad_tilemap_file("Bad tilemap file \"" + std::string("assets/tilemap.lua") + "\".");

        lua_getglobal(L, "tile_map");
        int table_ref = luaL_ref(L, LUA_REGISTRYINDEX);

        LuaTable table(*this, table_ref);

        struct
        {
            LuaValue bmp_file_name;
            LuaValue width, height, tile_width, tile_height;
            LuaValue tiles;
        } tile_map_lua;

        if (!table.get_value(LuaType::string, "bmp_file_name", tile_map_lua.bmp_file_name))
            throw bad_tilemap_file;
        if (!table.get_value(LuaType::_int, "width", tile_map_lua.width))
            throw bad_tilemap_file;
        if (!table.get_value(LuaType::_int, "height", tile_map_lua.height))
            throw bad_tilemap_file;
        if (!table.get_value(LuaType::_int, "tile_width", tile_map_lua.tile_width))
            throw bad_tilemap_file;
        if (!table.get_value(LuaType::_int, "tile_height", tile_map_lua.tile_height))
            throw bad_tilemap_file;
        if (!table.get_value(LuaType::table, "tiles", tile_map_lua.tiles))
            throw bad_tilemap_file;

        std::vector<LuaValue> tiles;
        tile_map_lua.tiles.get_table().to_array(tiles);
        */
    }

    void Lua::destroy()
    {
        auto L = (lua_State*)m_L;

        if (!m_scripts.empty())
        {
            for (auto script : m_scripts)
                delete script;

            m_scripts.clear();
        }

        m_next_script_id = 1;

        lua_close(L);
        m_L = nullptr;
    }

    int Lua::load_script(const std::string& file_name)
    {
        auto L = (lua_State*)m_L;

        //load file
        int result = luaL_loadfile(L, file_name.c_str());
        if (result != LUA_OK)
            throw_lua_err(L);

        //store file
        int script_ref = luaL_ref(L, LUA_REGISTRYINDEX);

        //run file
        //lua_rawgeti(L, LUA_REGISTRYINDEX, script_ref);
        /*
        result = lua_pcall(L, 0, LUA_MULTRET, 0);
        if (result != LUA_OK)
            throw_lua_err(L);
            */

        auto script = new LuaScript(*this, script_ref);
        script->m_id = m_next_script_id++;
        script->m_name = file_name;
        m_scripts.push_back(script);

        return script->m_id;
    }

    LuaScript* Lua::get_script(int id) const
    {
        for (auto script : m_scripts)
        {
            if (script->get_id() == id)
            {
                return script;
            }
        }

        return nullptr;
    }

    int Lua::get_script_id(const std::string& name) const
    {
        for (auto script : m_scripts)
        {
            if (script->get_name() == name)
            {
                return script->get_id();
            }
        }

        return 0;
    }

    int Lua::get_table_ref(const std::string& name) const
    {
        auto L = (lua_State*)m_L;

        lua_getglobal(L, name.c_str());
        if (lua_istable(L, -1))
        {
            return luaL_ref(L, LUA_REGISTRYINDEX);
        }

        throw Exception("Tried to get_table_ref on non-table.");

        return LUA_NOREF;
    }

    LuaValue Lua::get_value(int index) const
    {
        auto L = (lua_State*)m_L;

        int lt = lua_type(L, index);
        int table_ref;
        LuaValue value;
        switch (lt)
        {
        case LUA_TNUMBER:
            if (lua_isinteger(L, index))
                value = (int)lua_tointeger(L, index);
            else
                value = lua_tonumber(L, index);
            break;
        case LUA_TSTRING:
            value = lua_tostring(L, index);
            break;
        case LUA_TTABLE:
            lua_pushvalue(L, index);
            table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
            value = LuaTable((*(Lua*)this), table_ref);
            luaL_unref(L, LUA_REGISTRYINDEX, table_ref);
            break;
        }

        return value;
    }
}