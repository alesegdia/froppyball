#include "entities.h"

FroppyBall::FroppyBall()
    : m_circle(Constants::FroppyX, 0, Constants::FroppyBallRadius),
      m_renderable(sagl::createCircle(m_circle.radius()), GL_TRIANGLE_FAN, 1.f, 0.f, 0.5f)
{
    m_velocity.set(0, Constants::FroppyBallJumpImpulse);
    m_renderable.recalculateModelMatrix(m_circle.position().x(), m_circle.position().y());

}

sagl::Circle<float> &FroppyBall::circle()
{
    return m_circle;
}

void FroppyBall::update(bool player_touch)
{
    if( player_touch == true && m_lastPlayerTouchDown == false)
    {
        SAGL_LOGI("JUMP!");
        m_velocity.y(Constants::FroppyBallJumpImpulse);
    }
    else
    {
        m_velocity.y(m_velocity.y() + Constants::FroppyBallGravity);
        if( m_velocity.y() < -Constants::FroppyMaxYSpeed )
        {
            m_velocity.y(-Constants::FroppyMaxYSpeed);
        }
    }
    m_lastPlayerTouchDown = player_touch;
    m_circle.position() += m_velocity;

    m_renderable.recalculateModelMatrix(m_circle.position().x(), m_circle.position().y());
}

sagl::RenderablePrimitive FroppyBall::renderable()
{
    return m_renderable;
}

Wall::Wall(float x, float y, float w, float h)
    : m_renderable(
        sagl::createQuad(w, h),
        GL_TRIANGLES,
        0.f, 1.f, 0.f)
{
    m_rect.set(x, y, w, h);
    m_renderable.recalculateModelMatrix(m_rect.position().x(), m_rect.position().y());
}

sagl::Rect<float> &Wall::rect()
{
    return m_rect;
}

void Wall::update() {
    m_rect.position().x( m_rect.position().x() - Constants::FroppyBallHorizontalVelocity );
    m_renderable.recalculateModelMatrix(m_rect.position().x(), m_rect.position().y());
}

const sagl::RenderablePrimitive& Wall::renderable() const
{
    return m_renderable;
}
