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

int vis5d_color_table_set_alpha( float params[], float alpha )
{
   params[3] = alpha;
   if (alpha<0) {
      params[5] = 0;
      params[6] = 255;

      if (alpha == -2.0){
         params[2] = 0.0;
         params[3] = -1.0;
      }
      else{
         params[2] = 2.0;
      }
   }
   else {
      params[5] = alpha;
      params[6] = alpha;
      params[3] = alpha;
   }
   return 0;
}
