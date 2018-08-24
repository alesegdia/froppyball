#pragma once

#include <memory>
#include <GLES2/gl2.h>

#include "math.h"

namespace sagl {

/**
 * GpuBuffer represents a buffer in GPU in an extremely oversimplified take
 */
class GpuBuffer
{
public:

    typedef std::shared_ptr<GpuBuffer> SharedPtr;

    /**
     * Creates a buffer in the GPU with the desired configuration
     * @param buffer_data the data to upload
     * @param buffer_data_size_bytes the size in bytes of the data to upload
     * @param num_elements the number of elements (i.e.: vertices)
     * @param stride the stride
     * @param offset the data pointer offset
     * @param usage the usage
     * @param target the target
     */
    GpuBuffer( const GLfloat* buffer_data, GLuint buffer_data_size_bytes, GLuint num_elements, GLint num_components_per_vertex = 2, int stride = 0, void* offset = (void*)0, GLenum usage = GL_STATIC_DRAW, GLenum target = GL_ARRAY_BUFFER );

    ~GpuBuffer();

    /**
     * Binds the buffer with OpenGL
     */
    void bind();

    /**
     * Sets the buffer in a given attribute handle
     * @param index
     */
    void vertexAttribPointer(GLuint index);

    /**
     * The number of elements as in number of vectors
     * @return
     */
    GLuint numElements();

private:
    GLuint m_handle;
    int m_stride;
    void* m_offset;
    GLuint m_numElements;
    GLenum m_target;
    GLint m_componentsPerVertex;

};

GpuBuffer::SharedPtr createQuad(GLfloat width, GLfloat height);
GpuBuffer::SharedPtr createCircle( GLfloat radius, int num_divisions = 12 );

}