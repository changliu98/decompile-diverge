int CalcOffsetAndShift( int x, int y, size_t *offset, size_t *shift )
{
 int ret = -1;
 if( (x >= 0) && (x < 84) && (y >= 0) && (y < 48) && offset && shift )
 {
  *offset = (size_t) (x + (y / 8) * 84);
  *shift = (size_t) (y % 8);
  ret = 0;
 }
 return ret;
}