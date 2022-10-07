#include "LaserRaycastCallback.h"

float LaserRaycastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    auto object = reinterpret_cast<GameObject*>(fixture->GetBody()->GetUserData().pointer);
    if (object->get_type() == ObjectType::bullet || object->get_type() == ObjectType::enemy) {//if the hit object is an enemy or a bullet then call the handle collision method
        object->handle_collision(ObjectType::laser_beam);
    }

    m_fixture = fixture;
    m_point = point;
    m_normal = normal;
    m_fraction = fraction;
    return 0;
}
