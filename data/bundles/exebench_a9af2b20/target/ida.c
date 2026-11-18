char *__cdecl stpCpy(char *dest, const char *src)
{
  const char *v2; // rax

  while ( 1 )
  {
    v2 = src++;
    LOBYTE(v2) = *v2;
    *dest = (char)v2;
    if ( !(_BYTE)v2 )
      break;
    ++dest;
  }
  return dest;
}