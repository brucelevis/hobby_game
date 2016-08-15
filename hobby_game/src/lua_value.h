#pragma once

#include "lua_table.h"

#include <string>

namespace hg
{
    class LuaTable;

    class LuaValue
    {
    public:
        LuaValue();
        LuaValue(int i);
        LuaValue(float f);
        LuaValue(double d);
        LuaValue(const char* cs);
        LuaValue(const std::string& s);
        LuaValue(const LuaTable& t);

        LuaType get_type() const { return m_type; }
        int get_int() const { return m_number.as_int; }
        float get_float() const { return (float)m_number.as_double; }
        double get_double() const { return m_number.as_double; }
        const std::string& get_string() const { return m_string; }
        const LuaTable& get_table() const { return m_table; }

    private:
        LuaType m_type;

        union
        {
            int as_int;
            double as_double;
        } m_number;

        std::string m_string;

        LuaTable m_table;
    };
}