#pragma once

#include "component.h"

namespace hg
{
    class RenderScene;

    enum class RenderComponentType
    {
        sprite
    };

    class RenderComponent
        : public Component
    {
    public:
        RenderComponent(RenderScene& scene, int id, Level& level, int entity_id);
        virtual ~RenderComponent();

        ComponentType get_component_type() const override { return ComponentType::render; }

        virtual RenderComponentType get_render_type() const = 0;
    };
}