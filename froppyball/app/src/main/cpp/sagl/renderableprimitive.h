#pragma once

#include "gpubuffer.h"


namespace sagl {


/**
 * The RenderablePrimitive stores information about a GpuBuffer, color and
 * polygon rendering mode in order to be able to render 2D coloured shapes
 */
class RenderablePrimitive
{
public:
    RenderablePrimitive(GpuBuffer::SharedPtr buffer, GLenum mode, float r, float g, float b);

    /**
     * The OpenGL polygon rendering mode
     * @return the render mode
     */
    GLenum mode() const;

    /**
     * The GpuBuffer containing information about 2D vertices
     * @return the GpuBuffer
     */
    GpuBuffer::SharedPtr buffer() const;

    /**
     * The color to use when drawing this renderable
     * @return the color
     */
    const float* color() const;

    /**
     * Update the model matrix given a new position
     * @param x
     * @param y
     */
    void recalculateModelMatrix(float x, float y);

    /**
     * The model matrix
     * @return the model matrix
     */
    const Matrix4x4f& modelMatrix() const;


private:
    float m_color[3] = {0,0,0};
    GpuBuffer::SharedPtr m_buffer;
    GLenum m_mode;
    Matrix4x4f m_modelMatrix;

};

}
