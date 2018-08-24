#pragma once

#include <deque>

#include "sagl/math.h"
#include "sagl/renderer.h"
#include "sagl/gpubuffer.h"

#include "constants.h"
#include "entities.h"


/**
 * The Stage class represents the whole game scene with its actors, and is
 * responsible for updating and drawing them.
 */
class Stage
{
public:

    typedef std::shared_ptr<Stage> SharedPtr;

    Stage(sagl::Renderer::SharedPtr renderer);

    bool isGameOver();

    /**
     * Performs the game logic
     * @param touch_down tells if the screen is being touched
     * @param delta time between this frame and the previous one
     */
    void update(bool touch_down, double delta);

    /**
     * Renders the whole scene. This is, froppy, walls and floor.
     */
    void render();

private:

    /**
     * Spawns top and bottom walls at the spawn point with a randomly
     * placed gap in order to be able to travel through it.
     */
    void spawnWallPair();

    /**
     * Updates wall movement
     */
    void updateWalls();

    /**
     * Check collisions between froppy and all the walls.
     * @return
     */
    bool checkFroppyAgainstWalls();

    std::deque<Wall> m_walls;
    FroppyBall m_froppyBall;
    sagl::Renderer::SharedPtr m_renderer;
    bool m_gameOver = false;
    sagl::RenderablePrimitive m_floor;

};

