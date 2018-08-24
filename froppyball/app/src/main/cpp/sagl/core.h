#pragma once

#include <android/log.h>

#define SAGL_LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "sagl", __VA_ARGS__))
#define SAGL_LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "sagl", __VA_ARGS__))

namespace sagl
{

/**
 * Gets the current time
 * @return
 */
double get_time();

}

