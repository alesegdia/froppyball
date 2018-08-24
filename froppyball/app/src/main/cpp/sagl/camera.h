#pragma once

#include <memory>

#include "math.h"

namespace sagl {

class Camera
{
public:

    typedef std::shared_ptr<Camera> SharedPtr;

    Camera(int32_t vw, int32_t vh);

    /**
     * Sets the camera with ortographic projection
     * @param bottom
     * @param top
     * @param left
     * @param right
     * @param near
     * @param far
     */
    void orthographic( float bottom, float top, float left, float right, float near, float far );

    /**
     * Sets the camera with ortographic projection given a height using proper aspect ratio
     */
    void orthographic( float height );

    const Matrix4x4f& view() const;

    const Matrix4x4f& projection() const;

private:
    Matrix4x4f m_view;
    Matrix4x4f m_projection;
    float m_aspect;

};

}