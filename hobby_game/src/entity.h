#pragma once

#include "object.h"

namespace hg
{
    class Level;

    class Entity
        : public Object
    {
    public:
        Entity(Level& level, int id);
        ~Entity();

        Level& get_level() const { return m_level; }

    private:
        Level& m_level;
    };
}