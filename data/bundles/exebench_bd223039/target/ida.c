void __cdecl clearMarker(char *s, char marker)
{
  char *pos; // [rsp+8h] [rbp-18h]

  pos = strchr(s, marker);
  if ( pos )
    *pos = 0;
}