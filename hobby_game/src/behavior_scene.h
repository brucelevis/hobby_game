#pragma once

#include "component_scene.h"

namespace hg
{
    class Level;
    class BehaviorScript;

    class BehaviorScene
        : public ComponentScene
    {
    public:
        BehaviorScene();

        int create_script(int entity_id, int script_asset_id);
        BehaviorScript* get_script(int id) const;

    protected:
        friend class Level;

        void tick(float dt);

    private:

    };
}