void __cdecl toup(char *chr_ptr)
{
  if ( *chr_ptr >= 97 && *chr_ptr <= 122 )
    *chr_ptr -= 32;
}