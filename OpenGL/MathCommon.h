#pragma once
#include "Vector.h"

enum class Plane
{
    POSITIVEW = 0,
    RIGHT,
    LEFT,
    TOP,
    BOTTOM,
    FAR,
    NEAR
};

static bool IsInsidePlane(Plane plane, const vec4f& vertex)
{
    switch (plane)
    {
    case Plane::POSITIVEW:
        return vertex.w >= FLT_EPSILON;
    case Plane::RIGHT:
        return vertex.x <= vertex.w;
    case Plane::LEFT:
        return vertex.x >= -vertex.w;
    case Plane::TOP:
        return vertex.y <= vertex.w;
    case Plane::BOTTOM:
        return vertex.y >= -vertex.w;
    case Plane::FAR:
        return vertex.z <= vertex.w;
    case Plane::NEAR:
        return vertex.z >= -vertex.w;
    default:
        return false;
    }
}

static float GetIntersectionRatio(Plane plane, const vec4f& current, const vec4f& previous)
{
    switch (plane)
    {
    case Plane::POSITIVEW:
        return (previous.w - FLT_EPSILON) / (previous.w - current.w);
    case Plane::RIGHT:
        return (previous.w - previous.x) / ((previous.w - previous.x) - (current.w - current.x));
    case Plane::LEFT:
        return (previous.w + previous.x) / ((previous.w + previous.x) - (current.w + current.x));
    case Plane::TOP:
        return (previous.w - previous.y) / ((previous.w - previous.y) - (current.w - current.y));
    case Plane::BOTTOM:
        return (previous.w + previous.y) / ((previous.w + previous.y) - (current.w + current.y));
    case Plane::FAR:
        return (previous.w - previous.z) / ((previous.w - previous.z) - (current.w - current.z));
    case Plane::NEAR:
        return (previous.w + previous.z) / ((previous.w + previous.z) - (current.w + current.z));
    default:
        return 0;
    }

    return 0;
}