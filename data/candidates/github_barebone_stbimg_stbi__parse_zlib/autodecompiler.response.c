static int stbi__parse_zlib(stbi__zbuf *a, int parse_header)
{

   int final, type;
   if (parse_header)
      if (!stbi__parse_zlib_header(a)) return 0;


   else {
      a->m_bitcount = 0;
      a->m_bitbuf = 0;
      a->m_bytepos = 0;
   }

   do {
      final = stbi__zreceive(a,1);
      type = stbi__zreceive(a, 2);


      if (type == 0) {
         if (!stbi__parse_uncompressed_block(a)) return 0;
      } else if (type == 3)
         return 0;
      else {
         if (type == 1) {

            if (!stbi__zbuild_huffman(&a->litlencodes, stbi__zdefault_length, 288)) return 0;
            if (!stbi__zbuild_huffman(&a->distcodes, stbi__zdefault_distance, 32)) return 0;

         } else {

            if (!stbi__compute_huffman_codes(a)) return 0;
         }
         if (!stbi__parse_huffman_block(a)) return 0;
      }
   } while (!final);

   return 1;
}