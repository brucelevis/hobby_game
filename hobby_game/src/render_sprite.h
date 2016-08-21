#pragma once

#include "render_component.h"

#include <vecmath/vector.hpp>

namespace hg
{
    class RenderSprite
        : public RenderComponent
    {
    public:
        RenderSprite(RenderScene& scene, int id, Level& level, int entity_id);

        void set_texture_asset(int id);
        int get_texture_asset() const;

        RenderComponentType get_render_type() const override { return RenderComponentType::sprite; }

        const vcm::vec4& get_clip_rect() const { return m_clip_rect; }

    private:
        int m_texture_asset_id;
        vcm::vec4 m_clip_rect; //x, y, w, h
    };
}