int stbi__parse_zlib(struct stbi__zlib *z, int parse_header)
{
   int type; int final;
   if (parse_header && !stbi__zlib_parse_header(z))
      return 0;
   z->code_buffer = z->num_bits = 0;
   z->hit_zeof_once = 0;
   do
   {
      final = stbi__zlib_get_byte(z, 1);
      type = stbi__zlib_get_byte(z, 2);
      if (type == 0)
      {
         if (!stbi__zlib_decode_uncompressed(z))
            return 0;
      }
      else if (type == 3)
         return 0;
      else if (type == 1)
      {
         if (!stbi__zlib_decode_length(&z->z_length, stbi__zdefault_length, 288))
            return 0;
         if (!stbi__zlib_decode_length(&z->z_distance, stbi__zdefault_distance, 32))
            return 0;
      }
      else
      {
         if (!stbi__zlib_decode_length_and_offset(z))
            return 0;
      }
      if (!stbi__zlib_decode_copy(z))
         return 0;
   } while (!final);
   return 1;
}