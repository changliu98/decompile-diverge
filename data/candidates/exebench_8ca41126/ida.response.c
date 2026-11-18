char __cdecl zhalfstr(char *s)
{
  int back; // [rsp+0h] [rbp-18h]
  int nonzero; // [rsp+4h] [rbp-14h]
  int index; // [rsp+8h] [rbp-10h]
  char lastchar; // [rsp+Ch] [rbp-Ch]
  char nextchar; // [rsp+Eh] [rbp-Ah]
  char curchar; // [rsp+Fh] [rbp-9h]

  curchar = 48;
  lastchar = 48;
  index = -1;
  nonzero = 0;
  back = 0;
  while ( curchar )
  {
    nextchar = s[index + 1];
    s[index - back + 1] = 5 * (curchar & 1) + 48 + ((nextchar - 48) >> 1);
    if ( (char)(5 * (curchar & 1) + 48 + ((nextchar - 48) >> 1)) != 48 || nonzero )
      nonzero = 1;
    else
      ++back;
    lastchar = curchar;
    curchar = nextchar;
    ++index;
  }
  if ( index == back )
  {
    *s = 48;
    s[1] = 0;
  }
  else
  {
    s[index - back] = 0;
  }
  return lastchar;
}