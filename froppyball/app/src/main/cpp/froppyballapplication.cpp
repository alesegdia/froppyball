#include "froppyballapplication.h"


FroppyBallApplication::FroppyBallApplication(struct android_app *app)
        : Application(app)
{

}

int FroppyBallApplication::init()
{
    m_camera.reset( new sagl::Camera(windowWidth(), windowHeight()) );
    m_camera->orthographic(16);

    m_renderer.reset(new sagl::Renderer(m_camera.get()));
    m_stage.reset(new Stage(m_renderer));
    return 0;
}

void FroppyBallApplication::deinit()
{
    m_stage.reset();
    m_renderer.reset();
    m_camera.reset();
}

void FroppyBallApplication::render()
{
    glClearColor(0.1f, 0.4f, 1.f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, windowWidth(), windowHeight());

    m_renderer->begin();
    m_stage->render();
    m_renderer->end();
}

void FroppyBallApplication::update(double delta)
{
    m_stage->update( input().isTouchDown(), delta );
    if( m_stage->isGameOver() )
    {
        deinit();
        init();
    }
}




