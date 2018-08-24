#pragma once

#include <vector>

#include "sagl/sagl.h"

#include "stage.h"


class FroppyBallApplication : public sagl::Application
{
public:
    FroppyBallApplication(struct android_app* app);

    /**
     * Initializes the game status and all the graphics related objects
     * @return zero if success, non zero if otherwise
     */
    int init() override;

    /**
     * Destroys all graphics related objects
     */
    void deinit() override;

    /**
     * Renders the scene
     */
    void render() override;

    /**
     * Updates all needed objects
     * @param delta
     */
    void update(double delta) override;

private:
    Stage::SharedPtr m_stage;
    sagl::Renderer::SharedPtr m_renderer;
    sagl::Camera::SharedPtr m_camera;

};


