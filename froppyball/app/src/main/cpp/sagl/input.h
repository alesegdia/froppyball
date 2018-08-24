#pragma once

#include <cstdint>

#include <android_native_app_glue.h>

#include "math.h"

namespace sagl {

class Input
{
public:
    /**
     * Handles an input event
     * @param event
     * @return
     */
    int32_t handleInput(AInputEvent* event);
    bool isTouchDown();

private:
    Vec2<float> m_touch;
    bool m_touchDown;

};

}
