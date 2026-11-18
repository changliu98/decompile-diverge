void __cdecl byte2bits(char c, char *s)
{
  char v2; // cl
  char *v3; // rax
  int i; // [rsp+0h] [rbp-14h]

  i = 7;
  while ( i >= 0 )
  {
    v2 = i--;
    v3 = s++;
    *v3 = ((c >> v2) & 1) + 48;
  }
  *s = 0;
}