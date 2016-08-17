#pragma once

#include "object.h"
#include "component_type.h"

namespace hg
{
    class Level;
    class Entity;

    class ComponentScene;

    class Component
        : public Object
    {
    public:
        Component(ComponentScene& scene, int id, Level& level, int entity_id);
        virtual ~Component();

        Entity* get_entity() const;

        virtual ComponentType get_component_type() const = 0;

        Level& get_level() const { return m_level; }
        int get_entity_id() const { return m_entity_id; }

    private:
        Level& m_level;
        int m_entity_id;
    };
}