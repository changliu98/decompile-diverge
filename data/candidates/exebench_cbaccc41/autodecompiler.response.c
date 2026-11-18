int clip(double *x, double *y, double *z,
           double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
   int clipped = 0;

   if (*x < xmin) {
      *x = xmin;
      clipped = 1;
   } else if (*x > xmax) {
      *x = xmax;
      clipped = 1;
   }

   if (*y < ymin) {
      *y = ymin;
      clipped = 1;
   } else if (*y > ymax) {
      *y = ymax;
      clipped = 1;
   }

   if (*z < zmin) {
      *z = zmin;
      clipped = 1;
   } else if (*z > zmax) {
      *z = zmax;
      clipped = 1;
   }

   return clipped;
}