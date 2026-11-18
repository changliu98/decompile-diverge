int __cdecl toup(int c)
{
  if (c < 'a' || c > 'z')
    return c;
  else
    return c - 'a' + 'A';
}