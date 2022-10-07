#pragma once
#include "graphics\mesh_instance.h"
#include <maths/transform.h>
using gef::MeshInstance;
class Particle :
    public MeshInstance
{
public:
    Particle(float max_age);
    void update(const float delta_time);
    inline bool is_alive() { return is_alive_;};
    inline void set_start_transform(gef::Matrix44 transform) { start_transform_.Set(transform); };
    inline void set_end_transform(gef::Matrix44 transform) { end_transform_.Set(transform); };

private:
    gef::Transform start_transform_;
    gef::Transform end_transform_;
    float age_;
    const float max_age_;
    bool is_alive_;

};

