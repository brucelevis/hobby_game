#pragma once

#include "object_scene.h"

namespace hg
{
    class Level;
    class Component;

    class ComponentScene
        : public ObjectScene
    {
    public:
        ComponentScene();
        virtual ~ComponentScene();

        virtual Component* get_component(int id) const;
        virtual Component* get_component_of(int entity_id) const;

        Level* get_level() const { return m_level; }

    protected:
        friend class Level;

        virtual void init(Level& level);

    private:
        Level* m_level;
    };
}