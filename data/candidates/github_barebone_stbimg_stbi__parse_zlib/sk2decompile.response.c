static int stbi__parse_zlib(stbi__zbuf *a, int parse_header) {
  int btype, last;
  if (parse_header) {
    if (!stbi__parse_zlib_header(a)) return 0;
  }
  a->code_buffer = 0;
  a->code_length = 0;
  a->extra_bits = 0;
  do {
    last = stbi__zreceive(a, 1);
    btype = stbi__zreceive(a, 2);
    if (btype == 0) {
      if (!stbi__parse_uncompressed_block(a)) return 0;
    } else if (btype == 3) {
      return 0;
    } else {
      if (btype == 1) {
        if (!stbi__zbuild_huffman(&a->d_huff, stbi__zlib_length_code, 288))
          return 0;
        if (!stbi__zbuild_huffman(&a->d_huff_dist, stbi__zlib_dist_code, 32))
          return 0;
      } else {
        if (!stbi__compute_huffman_codes(a)) return 0;
      }
      if (!stbi__parse_huffman_block(a)) return 0;
    }
  } while (!last);
  return 1;
}