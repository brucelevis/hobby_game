#pragma once

#include "lua_type.h"

#include <vector>

namespace hg
{
    class Lua;
    class LuaValue;

    class LuaTable
    {
    public:
        LuaTable();
        LuaTable(Lua& lua, int table_ref);
        LuaTable(const LuaTable& t);
        LuaTable(LuaTable&& t);
        ~LuaTable();

        /*
            Creates a table from a Lua ref.
        */
        void create(Lua* lua, int table_ref);

        /*
            Destroys this table by destroying the Lua ref.
        */
        void destroy();

        /*
        out_value = table[key]
        Returns true if successfully got value.
        */
        bool get_value(LuaType out_type, const LuaValue& key, LuaValue& out_value) const;

        void to_array(std::vector<LuaValue>& out_array) const;

        LuaTable& operator=(const LuaTable& t);
        LuaTable& operator=(LuaTable&& t);

        int get_ref() const { return m_table_ref; }

    private:
        void check_basics() const;

    private:
        Lua* m_lua;
        int m_table_ref;
    };
}