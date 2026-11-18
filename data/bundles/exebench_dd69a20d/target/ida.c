void __cdecl remove_all_chars(char *str, char c)
{
  char *v2; // rax
  char *pw; // [rsp+0h] [rbp-20h]
  char *pr; // [rsp+8h] [rbp-18h]

  pr = str;
  pw = str;
  while ( *pr )
  {
    v2 = pr++;
    *pw = *v2;
    pw += *pw != c;
  }
  *pw = 0;
}