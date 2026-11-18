void __cdecl itoa(unsigned int value, char *buffer)
{
  int v2; // ecx
  int c; // [rsp+0h] [rbp-14h]

  c = 7;
  buffer[7] = 0;
  do
  {
    v2 = c--;
    buffer[v2] = value % 0xA + 48;
    value /= 0xAu;
  }
  while ( value );
}