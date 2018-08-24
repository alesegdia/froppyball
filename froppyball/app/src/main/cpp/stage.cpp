#include "stage.h"



Stage::Stage(sagl::Renderer::SharedPtr renderer)
        : m_renderer(renderer),
          m_floor(sagl::createQuad(40, 40), GL_TRIANGLES, 0.5f, 0.1f, 0.f)
{
    spawnWallPair();
    m_floor.recalculateModelMatrix(-10, -50);
}


void Stage::spawnWallPair()
{
    int minimum_height = 5;
    int rnd = rand() % 10 + minimum_height;
    int gap = 7;
    m_walls.push_front(Wall(Constants::WallSpawnX, -10, Constants::WallWidth, rnd));
    m_walls.push_front(Wall(Constants::WallSpawnX, -10 + rnd + gap, Constants::WallWidth, 20));
}

void Stage::updateWalls()
{
    for( auto& wall : m_walls )
    {
        wall.update();
    }
}

bool Stage::checkFroppyAgainstWalls()
{
    /**
     * This operation is currently being done without any care in performance
     * because there will be very few walls in play (no more than 10)
     */
    for( auto& wall : m_walls )
    {
        if( sagl::circle_collides_with_rect(m_froppyBall.circle(), wall.rect()) )
        {
            return true;
        }
    }
    return false;
}

void Stage::render()
{
    // render walls
    for( auto& wall : m_walls )
    {
        m_renderer->render(wall.renderable());
    }

    // render floor
    m_renderer->render(m_floor);

    // render froppy
    m_renderer->render(m_froppyBall.renderable());
}

bool Stage::isGameOver()
{
    return m_gameOver;
}

void Stage::update(bool touch_down, double delta)
{
    if( false == m_gameOver )
    {
        m_froppyBall.update(touch_down);

        m_gameOver = checkFroppyAgainstWalls();

        float froppy_y_pos = m_froppyBall.circle().position().y();
        if( froppy_y_pos > 15.f || froppy_y_pos < -10.f )
        {
            m_gameOver = true;
        }

        // update wall positions
        updateWalls();

        // check if we need to spawn a new pair of walls
        auto& last_wall = m_walls.front();
        if( Constants::WallSpawnX - last_wall.rect().x() >= Constants::DistanceBetweenWalls )
        {
            spawnWallPair();
        }

        // remove walls that are outside the view
        while( m_walls.back().rect().x() < Constants::WallVanishX )
        {
            m_walls.pop_back();
        }
    }

}
