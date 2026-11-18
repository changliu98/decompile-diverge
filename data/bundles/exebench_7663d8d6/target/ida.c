void __cdecl treemove(double *bb, double s, int d)
{
  if ( (d & 1) != 0 )
    *bb = s + *bb;
  else
    bb[3] = bb[3] - s;
  if ( (d & 2) != 0 )
    bb[1] = s + bb[1];
  else
    bb[4] = bb[4] - s;
  if ( (d & 4) != 0 )
    bb[2] = s + bb[2];
  else
    bb[5] = bb[5] - s;
}