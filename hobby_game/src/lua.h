#pragma once

#include <string>
#include <vector>

namespace hg
{
    class LuaImpl;
    class LuaValue;
    class LuaObject;
    class LuaTable;
    class LuaFunction;
    class LuaScript;

    class Lua
    {
    public:
        Lua();
        ~Lua();

    protected:
        friend class Game;

        /*
        Throws.
        */
        void init(const std::string& exe_dir);

        void destroy();

    public:
        /*
            Loads a script into memory.
            Returns the ID of the script -- which is used in get_script().
            Throws.
        */
        int load_script(const std::string& file_name);

        /*
            Returns a pointer to the script with this id.
            Returns null if no script exists with this id.
        */
        LuaScript* get_script(int id) const;

        /*
            Returns the script id of the script with this name.
            Returns 0 on failure (0 represents no id).
        */
        int get_script_id(const std::string& name) const;

        /*
            Returns a ref id that points to a table with this name in _G
        */
        int get_table_ref(const std::string& name) const;

        LuaValue get_value(int idx) const;

    protected:
        friend class LuaValue;
        friend class LuaObject;
        friend class LuaTable;
        friend class LuaFunction;
        friend class LuaScript;
        
        friend class LuaApi;

        void* get_L() const { return m_L; }

        static void throw_lua_err(void* L);

    private:
        void* m_L;

        int m_next_script_id;
        std::vector<LuaScript*> m_scripts;
    };
}