#pragma once

#include <memory>

#include <GLES2/gl2.h>

#include "core.h"


namespace sagl {


class Shader
{
public:

    typedef std::shared_ptr<Shader> SharedPtr;
    typedef std::unique_ptr<Shader> UniquePtr;

    Shader( const char* vs, const char* fs );

    ~Shader();

    /**
     * Binds an attrib location of this program
     * @param index
     * @param name
     */
    void bindAttribLocation(GLuint index, const GLchar* name);

    /**
     * Links the program
     * @return the status code
     */
    GLint link();

    /**
     * Activates the program
     */
    void use();

    /**
     * Gets the uniform location at specified string
     * @param name
     * @return
     */
    GLint uniformLocation(const GLchar* name);


private:

    /**
     * Loads the program
     * @param vs
     * @param fs
     * @return 0 on success, -1 on program object creation error, -2 on vs error, -3 on fs error
     */
    GLint loadProgram( const char* vs, const char* fs );

    /**
     * Loads a shader
     * @param shaderstr the shader string
     * @param type the shader type
     * @return a handle to the compiled shader
     */
    GLuint loadShader( const char* shaderstr, GLenum type );

    /**
     * Helper to log shader compiling and linking status
     * @param handle
     * @param what
     * @param getiv
     * @param getinfolog
     * @return
     */
    GLint checkStatus( GLuint handle, GLenum what, void(*getiv)(GLuint, GLenum, GLint*) = glGetProgramiv, void (*getinfolog)(GLuint, GLsizei, GLsizei*, GLchar*) = glGetProgramInfoLog );

    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_programObject;
    GLint m_result;

};


}