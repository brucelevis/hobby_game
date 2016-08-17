#pragma once

#include "component_scene.h"

namespace hg
{
    class PhysicsScene
        : public ComponentScene
    {
    public:
        PhysicsScene();

        int create_component(int entity_id) override;

    protected:
        friend class Level;

        void tick(float dt);

    private:
        
    };
}