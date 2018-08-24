#pragma once

#include "core.h"
#include "input.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

namespace sagl
{

class Application
{
public:

	Application(struct android_app* app);

    int exec();

protected:

    /**
     * Called when the application needs to be rendered
     */
    virtual void render() = 0 ;

    /**
     * Called when the application needs to be updated
     */
    virtual void update(double delta) = 0 ;

    /**
     * Let the client initialize the class
     * @return 0 if success, nonzero if not
     */
    virtual int init() = 0 ;

    /**
     * Let the client deinitialize the class
     */
    virtual void deinit() = 0 ;

    Input& input();

    int32_t windowWidth();

    int32_t windowHeight();

private:

    // Handle activity lifecycle command
    static void OnAppCommand( struct android_app* app, int32_t cmd ) ;
    void handleCommand( int32_t cmd ) ;

    // Handle activity input event
    static int32_t OnInputEvent(struct android_app* app, AInputEvent* event) ;
    int32_t handleEvent( AInputEvent* event ) ;

    /**
     * Process event queue
     */
    void processInput();

    int initGL();
    void deinitGL();

    struct android_app* m_app;

    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    int32_t m_width;
    int32_t m_height;
    bool m_running = true;
    bool m_term = true;

    double m_renderPeriod = 1e3 / 32;
    double m_updatePeriod = 1e3 / 32;

    Input m_input;

};

}
