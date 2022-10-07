#pragma once
#include "box2d/box2d.h"
#include "GameObject.h"
class LaserRaycastCallback :
    public b2RayCastCallback
{
public:
    LaserRaycastCallback()
    {
        m_fixture = NULL;
    }

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float fraction);

    b2Fixture* m_fixture;
    b2Vec2 m_point;
    b2Vec2 m_normal;
    float m_fraction;
};

