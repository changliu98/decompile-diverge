int zuchk_(double *yr, double *yi, int *nz, double *ascle, double *tol){
  double y1; double y2;
  double ymin; double ymax;
  double ymin2;
  *nz = 0;
  if ( *yr >= 0.0 )
    y1 = *yr;
  else
    y1 = - *yr;
  if ( *yi >= 0.0 )
    y2 = *yi;
  else
    y2 = - *yi;
  if ( y2 >= y1 )
    ymin = y1;
  else
    ymin = y2;
  if ( ymin <= *ascle ) {
    if ( y1 >= y2 )
      ymax = y1;
    else
      ymax = y2;
    if ( ymax / *tol > ymin )
      *nz = 1;
  }
  return 0;
}