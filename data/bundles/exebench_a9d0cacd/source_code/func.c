#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <time.h>

#include <sys/time.h>

#include <sys/resource.h>

#include <sys/stat.h>

#include <signal.h>

#include <unistd.h>

#include <X11/Xlib.h>

#include <X11/cursorfont.h>

int
vis5d_get_scene_formats(
 int *formats
)
{



 *formats = 1;

 return 0;
}
