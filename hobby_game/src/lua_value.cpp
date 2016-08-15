#include "lua_value.h"

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
}