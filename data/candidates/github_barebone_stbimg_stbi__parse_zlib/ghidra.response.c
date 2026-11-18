int stbi__parse_zlib(stbi__zbuf *a,int parse_header)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int type;
  int final;
  int parse_header_local;
  stbi__zbuf *a_local;
  int local_c;
  
  if ((parse_header == 0) || (iVar1 = stbi__parse_zlib_header(a), iVar1 != 0)) {
    a->num_bits = 0;
    a->code_buffer = 0;
    a->hit_zeof_once = 0;
    do {
      uVar2 = stbi__zreceive(a,1);
      uVar3 = stbi__zreceive(a,2);
      if (uVar3 == 0) {
        iVar1 = stbi__parse_uncompressed_block(a);
        if (iVar1 == 0) {
          return 0;
        }
      }
      else {
        if (uVar3 == 3) {
          return 0;
        }
        if (uVar3 == 1) {
          iVar1 = stbi__zbuild_huffman
                            (&a->z_length,
                             "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\b\b\b\b\b\b\b\b"
                             ,0x120);
          if (iVar1 == 0) {
            return 0;
          }
          iVar1 = stbi__zbuild_huffman
                            (&a->z_distance,
                             "\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05"
                             ,0x20);
          if (iVar1 == 0) {
            return 0;
          }
        }
        else {
          iVar1 = stbi__compute_huffman_codes(a);
          if (iVar1 == 0) {
            return 0;
          }
        }
        iVar1 = stbi__parse_huffman_block(a);
        if (iVar1 == 0) {
          return 0;
        }
      }
    } while (uVar2 == 0);
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}