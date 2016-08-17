#include "entity.h"
#include "level.h"

namespace hg
{
    Entity::Entity(Level& level, int id)
        : Object(level, id)
        , m_level(level)
    {

    }

    Entity::~Entity()
    {

    }
}