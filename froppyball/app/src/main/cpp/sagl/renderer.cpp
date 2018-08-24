
#include "renderer.h"


namespace sagl {


Renderer::Renderer(const Camera *camera)
        : m_camera(camera)
{
    m_shader.reset(new Shader(vs_str, fs_str));
    m_shader->bindAttribLocation(PositionIndex, "a_position");

    // if shader linking doesn't return zero, it has failed
    m_status = (0 == m_shader->link()) ? 0 : -1;
}

Renderer::~Renderer()
{

}

void Renderer::begin()
{
    assert(m_status == 0 && "The renderer has not been initialized with reset");
    m_shader->use();
    glEnableVertexAttribArray(PositionIndex);
    m_colorUniformLocation = m_shader->uniformLocation("u_color");
    m_orthoMatrixUniformLocation = m_shader->uniformLocation("u_vp");
    m_modelMatrixUniformLocation = m_shader->uniformLocation("u_model");
}

void Renderer::render(Matrix4x4f model, const float *color, GpuBuffer &gpubuffer, GLenum mode)
{
    gpubuffer.bind();
    gpubuffer.vertexAttribPointer(PositionIndex);
    glUniform4f( m_colorUniformLocation, color[0], color[1], color[2], 1.f );
    glUniformMatrix4fv( m_orthoMatrixUniformLocation, 1, GL_FALSE, m_camera->projection().data() );
    glUniformMatrix4fv( m_modelMatrixUniformLocation, 1, GL_FALSE, model.data() );
    glDrawArrays( mode, 0, gpubuffer.numElements() );
}

void Renderer::render(const RenderablePrimitive &rp)
{
    render( rp.modelMatrix(), rp.color(), *rp.buffer(), rp.mode() );
}

void Renderer::end()
{
    glDisableVertexAttribArray(PositionIndex);
}


}
