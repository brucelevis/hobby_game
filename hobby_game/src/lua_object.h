#pragma once

namespace hg
{
    class Lua;

    enum class LuaObjectType
    {
        table,
        function
    };

    class LuaObject
    {
    public:
        LuaObject();
        LuaObject(Lua& lua, int object_ref);
        LuaObject(const LuaObject& o);
        LuaObject(LuaObject&& o);
        virtual ~LuaObject();

        /*
        Creates an object from a Lua ref.
        */
        virtual void create(Lua* lua, int object_ref);

        /*
        Destroys this object by destroying the Lua ref.
        */
        virtual void destroy();

        LuaObject& operator=(const LuaObject& o);
        LuaObject& operator=(LuaObject&& o);

        int get_ref() const { return m_object_ref; }

    protected:
        void check_basics() const;

    protected:
        Lua* m_lua;
        int m_object_ref;
    };
}