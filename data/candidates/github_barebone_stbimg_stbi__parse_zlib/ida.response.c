int __cdecl stbi__parse_zlib(stbi__zbuf *a, int parse_header)
{
  int type; // [rsp+4h] [rbp-1Ch]
  int final; // [rsp+8h] [rbp-18h]

  if ( parse_header && !stbi__parse_zlib_header(a) )
    return 0;
  a->num_bits = 0;
  a->code_buffer = 0;
  a->hit_zeof_once = 0;
  do
  {
    final = stbi__zreceive(a, 1);
    type = stbi__zreceive(a, 2);
    if ( type )
    {
      if ( type == 3 )
        return 0;
      if ( type == 1 )
      {
        if ( !stbi__zbuild_huffman(&a->z_length, &stbi__zdefault_length, 288) )
          return 0;
        if ( !stbi__zbuild_huffman(&a->z_distance, &stbi__zdefault_distance, 32) )
          return 0;
      }
      else if ( !stbi__compute_huffman_codes(a) )
      {
        return 0;
      }
      if ( !stbi__parse_huffman_block(a) )
        return 0;
    }
    else if ( !stbi__parse_uncompressed_block(a) )
    {
      return 0;
    }
  }
  while ( !final );
  return 1;
}