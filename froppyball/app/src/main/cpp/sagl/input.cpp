#include "input.h"

namespace sagl {


int32_t Input::handleInput(AInputEvent* event)
{
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
    {
        int32_t action = AMotionEvent_getAction(event);
        if (action == AMOTION_EVENT_ACTION_DOWN)
        {
            m_touchDown = true;
            return 1;
        }
        else if (action == AMOTION_EVENT_ACTION_UP)
        {
            m_touchDown = false;
            return 1;
        }
    }
    return 0;
}

bool Input::isTouchDown()
{
    return m_touchDown;
}


}