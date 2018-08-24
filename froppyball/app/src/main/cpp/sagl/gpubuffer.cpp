
#include <cmath>

#include "gpubuffer.h"
#include "core.h"

namespace sagl {


std::shared_ptr<GpuBuffer> createQuad(GLfloat width, GLfloat height) {
    GLfloat w2, h2;
    w2 = width / 2.f;
    h2 = height / 2.f;

    GLfloat data[6 * 2] = {
        -0, -0,   width, 0,         width, height,
        -0, -0,   width, height,    0, height
    };

    return GpuBuffer::SharedPtr(new GpuBuffer(data, sizeof(data), 6));
}

std::shared_ptr<GpuBuffer> createCircle( GLfloat radius, int num_divisions )
{
    size_t num_2d_vertices = num_divisions + 2;
    size_t num_entities = (num_2d_vertices) * 2;
    GLfloat * data = new GLfloat[num_entities];
    float step = 2 * M_PI / num_divisions;
    size_t index = 0;
    data[index] = 0; index++;
    data[index] = 0; index++;
    for( float angle = 0; angle <= 2 * M_PI; angle += step )
    {
        float cx, cy;
        cx = cos(angle) * radius;
        cy = sin(angle) * radius;
        SAGL_LOGI("<%f, %f>", cx, cy);
        data[index] = cx; index++;
        data[index] = cy; index++;
        assert(index <= num_entities);
    }
    unsigned int size_in_bytes = sizeof(GLfloat) * num_entities;
    GpuBuffer::SharedPtr b(new GpuBuffer(data, size_in_bytes, num_2d_vertices));
    delete [] data;
    return b;
}


GpuBuffer::GpuBuffer(const GLfloat *buffer_data, GLuint buffer_data_size_bytes,
                     GLuint num_elements, GLint num_components_per_vertex, int stride,
                     void *offset, GLenum usage, GLenum target)
        : m_stride(stride),
          m_offset(offset),
          m_numElements(num_elements),
          m_target(target),
          m_componentsPerVertex(num_components_per_vertex)
{
    glGenBuffers( 1, &m_handle );
    glBindBuffer( target, m_handle );
    glBufferData( target, buffer_data_size_bytes, buffer_data, usage );
}

GpuBuffer::~GpuBuffer() {
    glDeleteBuffers(1, &m_handle);
}

void GpuBuffer::bind() {
    glBindBuffer( m_target, m_handle );
}

void GpuBuffer::vertexAttribPointer(GLuint index) {
    glVertexAttribPointer(
            index,
            m_componentsPerVertex,
            GL_FLOAT,
            GL_FALSE,
            m_stride,
            m_offset);
}

GLuint GpuBuffer::numElements() {
    return m_numElements;
}


}