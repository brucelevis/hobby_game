#pragma once

#include "component_scene.h"

namespace hg
{
    class Level;

    class PhysicsScene
        : public ComponentScene
    {
    public:
        PhysicsScene();

    protected:
        friend class Level;

        void tick(float dt);

    private:
        
    };
}