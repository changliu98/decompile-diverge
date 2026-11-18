int __cdecl toup(int c)
{
  if ( c < 97 || c > 122 )
    return c;
  else
    return c - 97 + 65;
}