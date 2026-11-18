void __cdecl cwk_path_fix_root(char *buffer, size_t buffer_size, size_t length)
{
  size_t i; // [rsp+0h] [rbp-20h]
  size_t lengtha; // [rsp+8h] [rbp-18h]

  lengtha = length;
  if ( !path_style )
  {
    if ( length > buffer_size )
      lengtha = buffer_size;
    for ( i = 0LL; i < lengtha; ++i )
    {
      if ( cwk_path_is_separator(&buffer[i]) )
        buffer[i] = *separators;
    }
  }
}