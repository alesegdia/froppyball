#include "shader.h"


namespace sagl {


Shader::Shader(const char *vs, const char *fs)
{
    m_result = loadProgram(vs, fs);
}

Shader::~Shader()
{
    if( m_programObject != 0 )
    {
        glDetachShader(m_programObject, m_vertexShader);
        glDetachShader(m_programObject, m_fragmentShader);

        glDeleteShader(m_vertexShader);
        glDeleteShader(m_fragmentShader);

        glDeleteProgram(m_programObject);
    }
}

void Shader::bindAttribLocation(GLuint index, const GLchar *name)
{
    glBindAttribLocation(m_programObject, index, name);
}

GLint Shader::link() {
    if( 0 != m_result )
    {
        return -1;
    }

    glLinkProgram(m_programObject);

    if( 0 == checkStatus( m_programObject, GL_LINK_STATUS ) )
    {
        glDeleteProgram(m_programObject);
        return -1;
    }


    return 0;
}

void Shader::use()
{
    glUseProgram(m_programObject);
}

GLint Shader::uniformLocation(const GLchar *name)
{
    return glGetUniformLocation(m_programObject, name);
}

GLint Shader::loadProgram(const char *vs, const char *fs)
{

    m_vertexShader = loadShader(vs, GL_VERTEX_SHADER);
    if( m_vertexShader == 0 )
    {
        return -2;
    }

    m_fragmentShader = loadShader(fs, GL_FRAGMENT_SHADER);
    if( m_fragmentShader == 0 )
    {
        return -3;
    }

    m_programObject = glCreateProgram();
    if( m_programObject == 0 )
    {
        return -1;
    }

    glAttachShader(m_programObject, m_vertexShader);
    glAttachShader(m_programObject, m_fragmentShader);

    SAGL_LOGI("%u", m_programObject);

    return 0;
}

GLuint Shader::loadShader(const char *shaderstr, GLenum type)
{
    GLuint handle = glCreateShader(type);

    if( handle != 0 )
    {
        glShaderSource( handle, 1, &shaderstr, NULL );
        glCompileShader( handle );

        if( 0 == checkStatus( handle, GL_COMPILE_STATUS, glGetShaderiv, glGetShaderInfoLog ) )
        {
            glDeleteShader(handle);
        }
    }

    return handle;
}

GLint Shader::checkStatus(GLuint handle, GLenum what, void (*getiv)(GLuint, GLenum, GLint *),
                          void (*getinfolog)(GLuint, GLsizei, GLsizei *, GLchar *))
{
    GLint success;
    getiv(handle, what, &success);
    if( 0 == success )
    {
        GLint log_length;
        getiv( handle, GL_INFO_LOG_LENGTH, &log_length );
        if( log_length > 1 )
        {
            char* log = new char[log_length];
            getinfolog(handle, log_length, NULL, log);
            SAGL_LOGW("%s", log);
            delete [] log;
        }
    }
    return success;
}


}
