#include "render_component.h"

#include "render_scene.h"

namespace hg
{
    RenderComponent::RenderComponent(RenderScene& scene, int id, Level& level, int entity_id)
        : Component(scene, id, level, entity_id)
    {
        
    }

    RenderComponent::~RenderComponent()
    {
        
    }
}