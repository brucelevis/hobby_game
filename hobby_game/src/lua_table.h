#pragma once

#include "lua_type.h"
#include "lua_object.h"

#include <vector>

namespace hg
{
    class LuaValue;

    class LuaTable
        : public LuaObject
    {
    public:
        LuaTable();

        /*
        out_value = table[key]
        Returns true if successfully got value.
        */
        bool get_value(LuaType out_type, const LuaValue& key, LuaValue& out_value) const;

        void to_array(std::vector<LuaValue>& out_array) const;
    };
}