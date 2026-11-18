int __cdecl stbi__parse_zlib(stbi__zbuf *a, int parse_header)
{
  int type;
  int final;
  int success = 1;

  if (parse_header && !stbi__parse_zlib_header(a))
    return 0;

  a->num_bits = 0;
  a->code_buffer = 0;
  a->hit_zeof_once = 0;

  do
  {
    final = stbi__zreceive(a, 1);
    type = stbi__zreceive(a, 2);

    if (type == 0)
    {
      // Stored (uncompressed) block
      success = stbi__parse_uncompressed_block(a);
    }
    else if (type == 3)
    {
      // Invalid block type
      success = 0;
    }
    else
    {
      // Compressed block (type 1: fixed Huffman, type 2: dynamic Huffman)
      if (type == 1)
      {
        success = stbi__zbuild_huffman(&a->z_length, &stbi__zdefault_length, 288) &&
                  stbi__zbuild_huffman(&a->z_distance, &stbi__zdefault_distance, 32);
      }
      else
      {
        success = stbi__compute_huffman_codes(a);
      }

      if (success)
      {
        success = stbi__parse_huffman_block(a);
      }
    }
  } while (success && !final);

  return success;
}