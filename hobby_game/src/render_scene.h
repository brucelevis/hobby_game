#pragma once

#include "component_scene.h"

namespace hg
{
    class Level;
    class RenderComponent;
    class RenderSprite;

    class RenderScene
        : public ComponentScene
    {
    public:
        RenderScene();

        int create_sprite(int entity_id);
        RenderSprite* get_sprite(int id) const;

    protected:
        friend class Level;

        void render();

    private:
        void render(RenderComponent* r);
        void render_sprite(RenderSprite* s);

    private:

    };
}