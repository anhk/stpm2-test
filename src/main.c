
#include "stpm2.h"
#include "stpm2_log.h"


int main(int argc, char **argv)
{
    stpm2_context ctx;

    int ret;

    ret = stpm2_init(&ctx);
    if (ret < 0) {
        LOG_ERROR("stpm2_init() failed");
        return 1;
    }

    return 0;
}
