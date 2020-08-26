#ifndef TUNE_STILL_ALIVE_H
#define TUNE_STILL_ALIVE_H
#include <stdint.h>

struct event_t {
  uint32_t time;
  uint8_t pitch;
};

static const struct event_t tune_still_alive[] = {
250,50+24,
250,50+24,
250,50-24,

500,52+24,
500,52-24,
500,52-24,

750,55+24,
750,55+24,
750,55-24,

1000,57+24,
1000,57+24,
1000,57-24,

1250,59+24,
1250,59+24,
1250,59-24,

1500,62+24,
1500,62+24,
1500,62-24,

1750,64+24,
1750,64+24,
1750,64-24,

2000,67+24,
2000,67+24,
2000,67-24,



};
#endif