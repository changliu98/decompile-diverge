int __cdecl substitute(char *data, char from, char to)
{
  char *v3; // rax
  char *ca; // [rsp+8h] [rbp-18h]

  while ( 1 )
  {
    ca = strchr(data, from);
    if ( !ca )
      break;
    v3 = ca;
    data = ca + 1;
    *v3 = to;
  }
  return 1;
}