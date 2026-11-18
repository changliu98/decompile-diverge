int str_linecount(char *text, int linelen, int *x)
{
  int lines = 1;
  for ( ; *text; text++ )
    if ( *text == '\n' )
    {
      lines++;
      *x = 0;
    }
    else if ( ++(*x) >= linelen )
    {
      lines++;
      *x = 0;
    }
  return lines;
}