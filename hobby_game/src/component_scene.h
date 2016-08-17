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

        virtual int create_component(int entity_id) = 0;

        virtual Component* get_component_of(int entity_id) const;

        Level* get_level() const { return m_level; }

    protected:
        virtual void init(Level& level);

    private:
        Level* m_level;
    };
}