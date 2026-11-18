void __cdecl convert_human(size_t size, size_t *nsize, char *c)
{
  int p; // [rsp+Ch] [rbp-1Ch]

  p = 0;
  while ( size > 0x400 )
  {
    size >>= 10;
    ++p;
  }
  switch ( p )
  {
    case 0:
      *c = 32;
      break;
    case 1:
      *c = 75;
      break;
    case 2:
      *c = 77;
      break;
    case 3:
      *c = 71;
      break;
    case 4:
      *c = 84;
      break;
    case 5:
      *c = 80;
      break;
    default:
      break;
  }
  *nsize = size;
}