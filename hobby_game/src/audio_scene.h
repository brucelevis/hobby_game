#pragma once

#include "component_scene.h"

namespace hg
{
    class AudioScene
        : public ComponentScene
    {
    public:
        AudioScene();

        int create_effect(int entity_id);

    private:

    };
}