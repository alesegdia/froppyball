#include "application.h"

#include <memory>



namespace sagl
{

Application::Application(struct android_app* app)
    : m_app(app)
{

}

int Application::initGL()
{
    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };
    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(m_app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, m_app->window, NULL);

    EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    context = eglCreateContext(display, config, NULL, contextAttribs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        SAGL_LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    SAGL_LOGI("sw: %d, sh: %d\n", w, h);

    m_display = display;
    m_context = context;
    m_surface = surface;
    m_width = w;
    m_height = h;

    // Check openGL on the system
    auto opengl_info = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
    for (auto name : opengl_info) {
        auto info = glGetString(name);
        SAGL_LOGI("OpenGL Info: %s", info);
    }

    // Initialize GL state.
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    return 0;
}


void Application::deinitGL()
{
    if (m_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_display, m_context);
        }
        if (m_surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_display, m_surface);
        }
        eglTerminate(m_display);
    }
    m_display = EGL_NO_DISPLAY;
    m_context = EGL_NO_CONTEXT;
    m_surface = EGL_NO_SURFACE;
}

int Application::exec()
{
    SAGL_LOGI("app started");
    m_app->userData = static_cast<void*>(this);
    m_app->onAppCmd = Application::OnAppCommand;
    m_app->onInputEvent = Application::OnInputEvent;

    double now, then, delta, update_timer, render_timer;
    now = then = sagl::get_time();
    delta = render_timer = update_timer = 0;

    while(m_running)
    {
        processInput();

        if( false == m_term )
        {
            now = sagl::get_time();
            delta = now - then;
            then = now;

            update_timer -= delta;
            render_timer -= delta;

            if( update_timer <= 0 )
            {
                update_timer += m_updatePeriod;
                update(delta);
            }

            if( render_timer <= 0 )
            {
                render_timer += m_renderPeriod;
                render();
                eglSwapBuffers(m_display, m_surface);
            }
        }
        else
        {
            now = then = sagl::get_time();
        }
    }

    return 0;
}

void Application::processInput()
{
    struct android_poll_source* source;
    while( ALooper_pollAll(0, NULL, NULL, reinterpret_cast<void**>(&source)) >= 0 )
    {
        if( source != NULL )
        {
            source->process(m_app, source);
        }
        if( m_app->destroyRequested != 0 )
        {
            deinitGL();
            return;
        }
    }
}

void Application::OnAppCommand( struct android_app* app, int32_t cmd )
{
    Application* iapp = static_cast<Application*>(app->userData);
    iapp->handleCommand(cmd);
}

void Application::handleCommand( int32_t cmd )
{
    switch(cmd)
    {
        case APP_CMD_INIT_WINDOW:
            SAGL_LOGI("init window command");
            initGL();
            init();

            render();
            m_term = false;
            break;
        case APP_CMD_TERM_WINDOW:
            SAGL_LOGI("term window command");
            deinit();
            deinitGL();
            m_term = true;
            break;
    }
}

int32_t Application::OnInputEvent(struct android_app *app, AInputEvent *event)
{
    Application* iapp = static_cast<Application*>(app->userData);
    return iapp->handleEvent(event);
}


int32_t Application::handleEvent( AInputEvent* event )
{
    return input().handleInput(event);
}

Input& Application::input()
{
    return m_input;
}

int32_t Application::windowWidth() {
    return m_width;
}

int32_t Application::windowHeight() {
    return m_height;
}

}
