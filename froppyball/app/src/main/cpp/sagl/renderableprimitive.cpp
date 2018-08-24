
#include "renderableprimitive.h"


namespace sagl {


sagl::RenderablePrimitive::RenderablePrimitive(GpuBuffer::SharedPtr buffer, GLenum mode, float r, float g, float b)
{
    m_color[0] = r; m_color[1] = g; m_color[2] = b;
    m_buffer = buffer;
    m_mode = mode;
    m_modelMatrix = Matrix4x4f::MakeIdentity();
    recalculateModelMatrix(0, 0);
}

GLenum RenderablePrimitive::mode() const {
    return m_mode;
}

GpuBuffer::SharedPtr RenderablePrimitive::buffer() const {
    return m_buffer;
}

const float *RenderablePrimitive::color() const {
    return m_color;
}

void RenderablePrimitive::recalculateModelMatrix(float x, float y) {
    m_modelMatrix = Matrix4x4f::MakeTranslation(x, y);
}

const Matrix4x4f &RenderablePrimitive::modelMatrix() const {
    return m_modelMatrix;
}


}
