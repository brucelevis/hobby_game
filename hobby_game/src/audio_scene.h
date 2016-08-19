#pragma once

#include "component_scene.h"

namespace hg
{
    class Level;
    class AudioEffect;

    class AudioScene
        : public ComponentScene
    {
    public:
        AudioScene();

        int create_effect(int entity_id);
        AudioEffect* get_effect(int id) const;

    protected:
        friend class Level;

    private:

    };
}