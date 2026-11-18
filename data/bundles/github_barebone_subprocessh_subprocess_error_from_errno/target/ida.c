int __cdecl subprocess_error_from_errno(int error)
{
  switch ( error )
  {
    case 1:
      return -5;
    case 2:
      return -4;
    case 12:
      return -6;
    case 13:
      return -5;
    case 20:
      return -4;
  }
  if ( (unsigned int)(error - 23) < 2 )
    return -6;
  return -1;
}