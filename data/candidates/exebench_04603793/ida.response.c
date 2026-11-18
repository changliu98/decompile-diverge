void __cdecl itoa(unsigned __int64 i, char *b)
{
  char *v2; // rax
  unsigned __int64 shifter; // [rsp+8h] [rbp-18h]
  unsigned __int64 ia; // [rsp+18h] [rbp-8h]

  ia = i;
  shifter = i;
  do
  {
    ++b;
    shifter /= 0xAuLL;
  }
  while ( shifter );
  *b = 0;
  do
  {
    v2 = b--;
    *(v2 - 1) = ia % 0xA + 48;
    ia /= 0xAuLL;
  }
  while ( ia );
}