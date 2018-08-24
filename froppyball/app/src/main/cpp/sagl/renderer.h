#pragma once

#include "sagl.h"
#include "gpubuffer.h"
#include "camera.h"
#include "renderableprimitive.h"

namespace sagl {


class Renderer
{
public:

    typedef std::shared_ptr<Renderer> SharedPtr;

    Renderer( const Camera* camera );

    ~Renderer();

    /**
     * Proper camera and shader configuration before starting to render
     */
    void begin();

    /**
     * Renders a GpuBuffer given a model matrix, a color and a rendering mode
     * @param model
     * @param color
     * @param gpubuffer
     * @param mode
     */
    void render( Matrix4x4f model, const float* color, GpuBuffer& gpubuffer, GLenum mode );

    /**
     * Renders a RenderablePrimitive
     * @param rp
     */
    void render( const RenderablePrimitive& rp );

    /**
     * Finalizes the rendering
     */
    void end();

private:

    static constexpr GLuint PositionIndex = 0;

    int m_status = -1;
    Shader::SharedPtr m_shader;

    GLint m_orthoMatrixUniformLocation;
    GLint m_colorUniformLocation;
    GLint m_modelMatrixUniformLocation;

    const Camera * m_camera;

    const GLchar* vs_str =
        "attribute vec2 a_position;\n"
        "varying vec4 v_color;\n"
        "uniform vec4 u_color;\n"
        "uniform mat4 u_vp;\n"
        "uniform mat4 u_model;\n"
        "void main() {\n"
        "   gl_Position = vec4(a_position, 0, 1) * u_model * u_vp;\n"
        "   v_color = u_color;\n"
        "}\n"
    ;

    const GLchar* fs_str =
        "precision mediump float;\n"
        "varying vec4 v_color;\n"
        "void main() {\n"
        "   gl_FragColor = v_color;\n"
        "}\n"
    ;

};

}

