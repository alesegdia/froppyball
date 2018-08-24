#include "camera.h"


namespace sagl {


Camera::Camera(int32_t vw, int32_t vh) {
    m_aspect = float(vw) / float(vh);
}

void Camera::orthographic(float bottom, float top, float left, float right, float near, float far)
{
    m_projection = Matrix4x4f::MakeOrtho(bottom, top, left, right, near, far);
}

void Camera::orthographic(float height)
{
    float width = height * m_aspect;
    orthographic(-height, height, -width, width, -2, 2);
}

const Matrix4x4f &Camera::view() const
{
    return m_view;
}

const Matrix4x4f &Camera::projection() const
{
    return m_projection;
}


}
