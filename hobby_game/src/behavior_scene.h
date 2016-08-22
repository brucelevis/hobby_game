#pragma once

#include "component_scene.h"

namespace hg
{
    class Level;

    class BehaviorScene
        : public ComponentScene
    {
    public:
        BehaviorScene();

    protected:
        friend class Level;

    private:

    };
}