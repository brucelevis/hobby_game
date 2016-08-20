#pragma once

#include "component_scene.h"

namespace hg
{
    class Level;
    class PhysicsEmpty;

    class PhysicsScene
        : public ComponentScene
    {
    public:
        PhysicsScene();

        int create_empty(int entity_id);
        PhysicsEmpty* get_empty(int id) const;

    protected:
        friend class Level;

        void tick(float dt);

    private:
        
    };
}