char *__cdecl getbase(char *p, int *basep)
{
  char *v3; // [rsp+18h] [rbp-8h]

  if ( *p == 48 )
  {
    switch ( p[1] )
    {
      case 'n':
      case 't':
        *basep = 10;
        goto LABEL_7;
      case 'o':
        *basep = 8;
        goto LABEL_7;
      case 'x':
        *basep = 16;
LABEL_7:
        v3 = p + 2;
        break;
      default:
        *basep = 10;
        v3 = p;
        break;
    }
  }
  else
  {
    *basep = 10;
    return p;
  }
  return v3;
}