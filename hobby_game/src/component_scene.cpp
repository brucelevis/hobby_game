#include "component_scene.h"

#include "component.h"

namespace hg
{
    ComponentScene::ComponentScene()
        : m_level()
    {

    }

    ComponentScene::~ComponentScene()
    {

    }

    void ComponentScene::init(Level& level)
    {
        m_level = &level;
    }

    Component* ComponentScene::get_component(int id) const
    {
        return (Component*)get_object(id);
    }

    Component* ComponentScene::get_component_of(int entity_id) const
    {
        auto objects = get_objects();
        for (int i = 0; i < get_num_objects(); ++i)
        {
            auto c = (Component*)(objects[i]);
            if (c->get_entity_id() == entity_id)
            {
                return c;
            }
        }

        return nullptr;
    }
}