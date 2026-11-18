#include <ctype.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <math.h>

#include <time.h>

#include <unistd.h>

#include <X11/Xlib.h>

#include <X11/Xutil.h>

#include <X11/Xatom.h>

#include <X11/keysym.h>

#include <X11/XKBlib.h>

void SwapIEEE32(char W[4])
{
   char B;

   B = W[0]; W[0] = W[3]; W[3] = B;
   B = W[1]; W[1] = W[2]; W[2] = B;
}
