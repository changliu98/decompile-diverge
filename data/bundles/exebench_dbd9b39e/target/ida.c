void __cdecl stress_chop(char *str, const char ch_0)
{
  char *ptr; // [rsp+8h] [rbp-18h]

  ptr = strchr(str, ch_0);
  if ( ptr )
    *ptr = 0;
}