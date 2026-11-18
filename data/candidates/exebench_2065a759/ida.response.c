int __cdecl set_filename(char *to_name, char *from_name)
{
  while ( *from_name )
  {
    if ( *from_name == 47 )
    {
      *to_name = 0;
      return 2;
    }
    *to_name++ = *from_name++;
  }
  *to_name = 0;
  return 1;
}