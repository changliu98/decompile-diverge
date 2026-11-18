void __cdecl char_replace(char *str, char origc, char newc)
{
  char *v3; // rax

  while ( 1 )
  {
    v3 = str++;
    if ( !*v3 )
      break;
    if ( *str == origc )
      *str = newc;
  }
}