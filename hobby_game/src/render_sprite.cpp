#include "render_sprite.h"
#include "render_scene.h"

namespace hg
{
    RenderSprite::RenderSprite(RenderScene& scene, int id, Level& level, int entity_id)
        : RenderComponent(scene, id, level, entity_id)
    {

    }
}