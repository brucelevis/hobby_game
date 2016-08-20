#pragma once

#include "render_component.h"

namespace hg
{
    class RenderSprite
        : public RenderComponent
    {
    public:
        RenderSprite(RenderScene& scene, int id, Level& level, int entity_id);

        RenderComponentType get_render_type() const override { return RenderComponentType::sprite; }

    private:

    };
}