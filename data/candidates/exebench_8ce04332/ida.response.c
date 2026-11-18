void __cdecl int2str(int value, int i, char *output)
{
  char *v3; // rax

  while ( i )
  {
    v3 = output++;
    *v3 = value / i % 10 + 48;
    i /= 10;
  }
}