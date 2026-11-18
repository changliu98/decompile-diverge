void __cdecl charset_remove(char *buffer, char value)
{
  char *v2; // rax
  char *r; // [rsp+0h] [rbp-20h]
  char *l; // [rsp+8h] [rbp-18h]

  l = buffer;
  for ( r = buffer; *r; ++r )
  {
    if ( *r != value )
    {
      v2 = l++;
      *v2 = *r;
    }
  }
  *l = 0;
}