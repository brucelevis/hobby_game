#include "render_sprite.h"
#include "render_scene.h"

#include "level.h"
#include "game.h"
#include "texture_asset.h"
#include "bitmap_asset.h"

namespace hg
{
    RenderSprite::RenderSprite(RenderScene& scene, int id, Level& level, int entity_id)
        : RenderComponent(scene, id, level, entity_id)

        , m_texture_asset_id()
    {

    }

    void RenderSprite::set_texture_asset(int id)
    {
        if (m_texture_asset_id != id)
        {
            m_texture_asset_id = id;

            const auto& texture = get_level().get_game()->get_assets().get_texture(m_texture_asset_id)->get_texture();
            if (texture.exists())
            {
                vcm::vec2 scale = vcm::vec2(1.0f / texture.get_width(), 1.0f / texture.get_height());
                m_clip_rect = vcm::vec4(0.0f, 0.0f, texture.get_width(), texture.get_height()) * vcm::vec4(scale, scale);
            }
        }
    }

    int RenderSprite::get_texture_asset() const
    {
        return m_texture_asset_id;
    }
}