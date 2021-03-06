#include "lua.h"
#include "exception.h"

#include "lua_value.h"
#include "lua_table.h"
#include "lua_script.h"
#include "lua_function.h"

#include <lua.hpp>

#include <string>
#include <iostream>

namespace hg
{
    void Lua::throw_lua_err(void* L_)
    {
        auto L = (lua_State*)L_;

        Exception err(std::string("Lua error: ") + lua_tostring(L, -1));
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

    void Lua::init(const std::string& exe_dir)
    {
        m_L = luaL_newstate();
        auto L = (lua_State*)m_L;

        luaL_openlibs(L);

        std::string pkg_path_fix = "package.path = package.path .. ";
        pkg_path_fix += "';" + exe_dir + "../assets/?.lua'";

        std::string folders[] = { "bitmaps", "prefabs", "sounds", "textures", "tilemaps", "behaviors" };

        for (auto folder : folders)
        {
            pkg_path_fix += " .. ';" + folder + "/?.lua'";
        }

        luaL_dostring(L, pkg_path_fix.c_str());

        luaL_loadfile(L, "assets/test.lua");

        int err = lua_pcall(L, 0, LUA_MULTRET, 0);
        if (err)
        {
            throw_lua_err(L);
        }

        lua_getglobal(L, "test");

        int test_ref = luaL_ref(L, LUA_REGISTRYINDEX);
        LuaFunction f;
        f.create(this, test_ref);
        luaL_unref(L, LUA_REGISTRYINDEX, test_ref);
        
        LuaValue params[] = { 1, 2, 3 };
        std::vector<LuaValue> results;
        f.call(params, 3, results);

        for (int i = 0; i < results.size(); ++i)
            std::cout << (int)results[i].get_type() << std::endl;
    }

    void Lua::destroy()
    {
        if (m_L)
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
        LuaValue value;

        value.pull(*this, index, LuaType::undefined);

        return value;
    }
}