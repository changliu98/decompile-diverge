void pick(int *pos, int *row)
{
  if ( ++(*row) >= 768 )
  {
    ++(*pos);
    (*row) = 0;
  }
  if ( *pos >= 180 )
    *pos = 0;
}