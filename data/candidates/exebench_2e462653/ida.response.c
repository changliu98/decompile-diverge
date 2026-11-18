int __cdecl str_linecount(char *str, int linelen, int *x)
{
  int lines; // [rsp+0h] [rbp-1Ch]

  lines = 1;
  while ( *str )
  {
    if ( *str == 10 )
    {
      ++lines;
      *x = 0;
    }
    else if ( ++*x >= linelen )
    {
      ++lines;
      *x = 0;
    }
    ++str;
  }
  return lines;
}