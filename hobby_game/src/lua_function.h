#pragma once

#include "lua_type.h"
#include "lua_object.h"

#include <vector>

namespace hg
{
    class LuaValue;

    class LuaFunction
        : public LuaObject
    {
    public:
        LuaFunction();

        /*
            Throws.
        */
        void call(const LuaValue* params, int num_params, std::vector<LuaValue>& out_results);
    };
}