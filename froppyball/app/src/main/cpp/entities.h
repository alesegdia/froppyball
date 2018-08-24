#pragma once

#include "sagl/sagl.h"
#include "constants.h"


/**
 * The FroppyBall class contains the representation both
 * physical and visual of the Froppy Ball, the protagonist,
 * as well as the code needed to update its state
 */
class FroppyBall
{
public:

    FroppyBall();

    sagl::Circle<float>& circle();
    void update(bool player_touch);
    sagl::RenderablePrimitive renderable();

private:
    sagl::Circle<float> m_circle;
    sagl::Vec2<float> m_velocity;
    bool m_lastPlayerTouchDown = false;
    sagl::RenderablePrimitive m_renderable;

};


/**
 * The Wall class represents a wall with which Froppy
 * can collide and lose. These walls will be all moving left.
 */
class Wall
{
public:

    Wall( float x, float y, float w, float h );

    sagl::Rect<float>& rect();
    void update();
    const sagl::RenderablePrimitive& renderable() const ;


private:
    sagl::Rect<float> m_rect;
    sagl::RenderablePrimitive m_renderable;

};
