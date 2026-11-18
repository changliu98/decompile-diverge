#include <unistd.h>

#include <string.h>

#include <stdio.h>

#include <sys/mman.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <errno.h>

#include <ctype.h>

#include <stdlib.h>

#include <time.h>

#include <locale.h>

static float get_color_value(int attr, float c[3], float b[3], float g[3])
{
    switch (attr & (((1 << 3)|(1 << 4)|(1 << 5)) | ((1 << 0)|(1 << 1)|(1 << 2)))) {
    case ((1 << 3) | (1 << 0)): return c[0];
    case ((1 << 3) | (1 << 1)): return c[1];
    case ((1 << 3) | (1 << 2)): return c[2];
    case ((1 << 4) | (1 << 0)): return b[0];
    case ((1 << 4) | (1 << 1)): return b[1];
    case ((1 << 4) | (1 << 2)): return b[2];
    case ((1 << 5) | (1 << 0)): return g[0];
    case ((1 << 5) | (1 << 1)): return g[1];
    case ((1 << 5) | (1 << 2)): return g[2];
    default: return 0.0;
    }
}
