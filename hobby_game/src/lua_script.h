#pragma once

#include "lua_value.h"

#include <string>
#include <vector>

namespace hg
{
    class Lua;

    class LuaScript
    {
    public:
        LuaScript();
        LuaScript(Lua& lua, int script_ref);

        /*
            Throws.
        */
        void run();

        /*
            Same as run() except stores the return values in a list.
        */
        void run(std::vector<LuaValue>& out_returns);

        int get_id() const { return m_id; }
        const std::string& get_name() const { return m_name; }

    protected:
        friend class Lua;

        int m_id;
        std::string m_name;

    private:
        Lua* m_lua;
        int m_script_ref;
    };
}