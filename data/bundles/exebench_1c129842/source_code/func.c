#include <ffi.h>

#include <stdio.h>

#include <stdlib.h>

#include <dlfcn.h>

#include <string.h>

void
add_four(int *a) {
 *a += 4;
}
