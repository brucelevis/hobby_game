#include "render_scene.h"

#include "render_component.h"
#include "render_sprite.h"

#include "level.h"
#include "physics_component.h"
#include "game.h"
#include "texture_asset.h"

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

        auto asset = get_level()->get_game()->get_assets().get_texture(s->get_texture_asset());
        const auto& texture = asset->get_texture();
        if (asset && texture.exists())
        {
            texture.use();
        }

        vcm::vec4 clip = s->get_clip_rect();
        float w = (float)texture.get_width();
        float h = (float)texture.get_height();

        glBegin(GL_QUADS);

        glTexCoord2f(clip.x, clip.y);
        glVertex2f(position.x, position.y);

        glTexCoord2f(clip.x, clip.y + clip.w);
        glVertex2f(position.x, position.y + h);

        glTexCoord2f(clip.x + clip.z, clip.y + clip.w);
        glVertex2f(position.x + w, position.y + h);

        glTexCoord2f(clip.x + clip.z, clip.y);
        glVertex2f(position.x + w, position.y);

        glEnd();
    }
}