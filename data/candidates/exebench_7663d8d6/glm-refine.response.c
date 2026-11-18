void __cdecl treemove(double *bb, double s, int d)
{
  // bb represents a 3D Axis-Aligned Bounding Box (AABB) 
  // bb[0..2] are the minimum bounds (x, y, z)
  // bb[3..5] are the maximum bounds (x, y, z)
  // s is the size/step to move
  // d is a direction bitmask (bit 0: +X/-X, bit 1: +Y/-Y, bit 2: +Z/-Z)

  // X-axis
  if ( (d & 1) != 0 )
    bb[0] += s;
  else
    bb[3] -= s;

  // Y-axis
  if ( (d & 2) != 0 )
    bb[1] += s;
  else
    bb[4] -= s;

  // Z-axis
  if ( (d & 4) != 0 )
    bb[2] += s;
  else
    bb[5] -= s;
}