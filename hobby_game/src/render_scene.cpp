#include "render_scene.h"

#include "render_component.h"
#include "render_sprite.h"

#include "level.h"
#include "physics_component.h"

#include <GL/glew.h>

namespace hg
{
    RenderScene::RenderScene()
    {

    }

    int RenderScene::create_sprite(int entity_id)
    {
        auto effect = new RenderSprite(*this, new_object_id(), *get_level(), entity_id);
        return create_object(effect);
    }

    RenderSprite* RenderScene::get_sprite(int id) const
    {
        auto o = (RenderComponent*)get_object(id);
        if (o->get_render_type() == RenderComponentType::sprite)
            return (RenderSprite*)o;

        return nullptr;
    }

    void RenderScene::render()
    {
        auto objects = get_objects();
        int count = get_num_objects();

        for (int i = 0; i < count; ++i)
        {
            auto r = (RenderComponent*)(objects[i]);
            render(r);
        }
    }

    void RenderScene::render(RenderComponent* r)
    {
        switch (r->get_render_type())
        {
        case RenderComponentType::sprite:
            render_sprite((RenderSprite*)r);
            break;
        }
    }

    void RenderScene::render_sprite(RenderSprite* s)
    {
        auto physics = (PhysicsComponent*)get_level()->get_component_of(s->get_entity_id(), ComponentType::physics);
        vcm::vec2 position;
        if (physics)
        {
            position = physics->get_position();
        }
        
        float w = 32.0f, h = 32.0f;

        glBegin(GL_QUADS);
        glVertex2f(position.x, position.y);
        glVertex2f(position.x, position.y + h);
        glVertex2f(position.x + w, position.y + h);
        glVertex2f(position.x + w, position.y);
        glEnd();
    }
}