#include "core.h"

#include <time.h>

namespace sagl
{

double get_time()
{
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
}

}
