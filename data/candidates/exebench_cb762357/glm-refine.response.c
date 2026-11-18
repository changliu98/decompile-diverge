void __cdecl scale_mat(matrix2x3 *m, int sx, int sy)
{
  // Scale the X components (columns 0, 2, and 4)
  if ( sx != FP_SCALE_1024 )
  {
    m->m00 = (sx * m->m00) / FP_SCALE_1024;
    m->m10 = (sx * m->m10) / FP_SCALE_1024;
    m->m20 = (sx * m->m20) / FP_SCALE_1024;
  }

  // Scale the Y components (columns 1, 3, and 5)
  if ( sy != FP_SCALE_1024 )
  {
    m->m01 = (sy * m->m01) / FP_SCALE_1024;
    m->m11 = (sy * m->m11) / FP_SCALE_1024;
    m->m21 = (sy * m->m21) / FP_SCALE_1024;
  }
}