#include "component.h"
#include "component_scene.h"

#include "level.h"

namespace hg
{
    Component::Component(ComponentScene& scene, int id, Level& level, int entity_id)
        : Object(scene, id)
        , m_level(level)
        , m_entity_id(entity_id)
    {

    }

    Component::~Component()
    {

    }

    Entity* Component::get_entity() const
    {
        return m_level.get_entity(m_entity_id);
    }
}