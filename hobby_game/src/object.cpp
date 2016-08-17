#include "object.h"

namespace hg
{
    Object::Object(ObjectScene& scene, int id)
        : m_scene(scene)
        , m_id(id)
    {

    }

    Object::~Object()
    {

    }
}