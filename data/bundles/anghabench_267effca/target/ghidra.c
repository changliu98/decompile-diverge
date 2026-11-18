uint32_t _ccv_sparse_matrix_index_for_hash(uint32_t hash,int prime_index)

{
  int prime_index_local;
  uint32_t hash_local;
  uint local_c;
  
  local_c = hash;
  switch(prime_index) {
  case 0:
    local_c = 0;
    break;
  case 1:
    local_c = hash & 1;
    break;
  case 2:
    local_c = hash % 3;
    break;
  case 3:
    local_c = hash % 5;
    break;
  case 4:
    local_c = hash % 7;
    break;
  case 5:
    local_c = hash % 0xb;
    break;
  case 6:
    local_c = hash % 0xd;
    break;
  case 7:
    local_c = hash % 0x11;
    break;
  case 8:
    local_c = hash % 0x17;
    break;
  case 9:
    local_c = hash % 0x1d;
    break;
  case 10:
    local_c = hash % 0x25;
    break;
  case 0xb:
    local_c = hash % 0x2f;
    break;
  case 0xc:
    local_c = hash % 0x3b;
    break;
  case 0xd:
    local_c = hash % 0x49;
    break;
  case 0xe:
    local_c = hash % 0x61;
    break;
  case 0xf:
    local_c = hash % 0x7f;
    break;
  case 0x10:
    local_c = hash % 0x97;
    break;
  case 0x11:
    local_c = hash % 0xc5;
    break;
  case 0x12:
    local_c = hash % 0xfb;
    break;
  case 0x13:
    local_c = hash % 0x139;
    break;
  case 0x14:
    local_c = hash % 0x18d;
    break;
  case 0x15:
    local_c = hash % 499;
    break;
  case 0x16:
    local_c = hash % 0x277;
    break;
  case 0x17:
    local_c = hash % 0x31d;
    break;
  case 0x18:
    local_c = hash % 0x3f1;
    break;
  case 0x19:
    local_c = hash % 0x4eb;
    break;
  case 0x1a:
    local_c = hash % 0x63d;
    break;
  case 0x1b:
    local_c = hash % 0x7db;
    break;
  case 0x1c:
    local_c = hash % 0x9eb;
    break;
  case 0x1d:
    local_c = hash % 0xc83;
    break;
  case 0x1e:
    local_c = hash % 0xfbb;
    break;
  case 0x1f:
    local_c = hash % 0x13df;
    break;
  case 0x20:
    local_c = hash % 0x1915;
    break;
  case 0x21:
    local_c = hash % 0x1f99;
    break;
  case 0x22:
    local_c = hash % 0x27d1;
    break;
  case 0x23:
    local_c = hash % 0x3235;
    break;
  case 0x24:
    local_c = hash % 0x3f41;
    break;
  case 0x25:
    local_c = hash % 0x4faf;
    break;
  case 0x26:
    local_c = hash % 0x6475;
    break;
  case 0x27:
    local_c = hash % 0x7e91;
    break;
  case 0x28:
    local_c = hash % 0x9f77;
    break;
  case 0x29:
    local_c = hash % 0xc8ed;
    break;
  case 0x2a:
    local_c = hash % 0xfd2b;
    break;
  case 0x2b:
    local_c = hash % 0x13ef1;
    break;
  case 0x2c:
    local_c = hash % 0x191dd;
    break;
  case 0x2d:
    local_c = hash % 0x1fa47;
    break;
  case 0x2e:
    local_c = hash % 0x27deb;
    break;
  case 0x2f:
    local_c = hash % 0x323bf;
    break;
  case 0x30:
    local_c = hash % 0x3f49d;
    break;
  case 0x31:
    local_c = hash % 0x4fbd9;
    break;
  case 0x32:
    local_c = hash % 0x64787;
    break;
  case 0x33:
    local_c = hash % 0x7e96d;
    break;
  case 0x34:
    local_c = hash % 0x9f7d3;
    break;
  case 0x35:
    local_c = hash % 0xc8f4d;
    break;
  case 0x36:
    local_c = hash % 0xfd303;
    break;
  case 0x37:
    local_c = hash % 0x13efe9;
    break;
  case 0x38:
    local_c = hash % 0x191e9d;
    break;
  case 0x39:
    local_c = hash % 0x1fa611;
    break;
  case 0x3a:
    local_c = hash % 0x27dfed;
    break;
  case 0x3b:
    local_c = hash % 0x323d49;
    break;
  case 0x3c:
    local_c = hash % 0x3f4c37;
    break;
  case 0x3d:
    local_c = hash % 0x4fbffb;
    break;
  case 0x3e:
    local_c = hash % 0x647a97;
    break;
  case 0x3f:
    local_c = hash % 0x7e9869;
    break;
  case 0x40:
    local_c = hash % 0x9f800f;
    break;
  case 0x41:
    local_c = hash % 0xc8f539;
    break;
  case 0x42:
    local_c = hash % 0xfd30e7;
    break;
  case 0x43:
    local_c = hash % 0x13f0031;
    break;
  case 0x44:
    local_c = hash % 0x191ea81;
    break;
  case 0x45:
    local_c = hash % 0x1fa61e9;
    break;
  case 0x46:
    local_c = hash % 0x27e0081;
    break;
  case 0x47:
    local_c = hash % 0x323d521;
    break;
  case 0x48:
    local_c = hash % 0x3f4c409;
    break;
  case 0x49:
    local_c = hash % 0x4fc012d;
    break;
  case 0x4a:
    local_c = hash % 0x647aa43;
    break;
  case 0x4b:
    local_c = hash % 0x7e987ef;
    break;
  case 0x4c:
    local_c = hash % 0x9f80263;
    break;
  case 0x4d:
    local_c = hash % 0xc8f5489;
    break;
  case 0x4e:
    local_c = hash % 0xfd31009;
    break;
  case 0x4f:
    local_c = hash % 0x13f004cb;
    break;
  case 0x50:
    local_c = hash % 0x191ea927;
    break;
  case 0x51:
    local_c = hash % 0x1fa61ffd;
    break;
  case 0x52:
    local_c = hash % 0x27e009b9;
    break;
  case 0x53:
    local_c = hash % 0x323d525b;
    break;
  case 0x54:
    local_c = hash % 0x3f4c3ff9;
    break;
  case 0x55:
    local_c = hash % 0x4fc01359;
    break;
  case 0x56:
    local_c = hash % 0x647aa4bf;
    break;
  case 0x57:
    local_c = hash % 0x7e987ff7;
    break;
  case 0x58:
    local_c = hash % 0x9f8026c9;
    break;
  case 0x59:
    local_c = hash % 0xc8f54987;
    break;
  case 0x5a:
    local_c = hash % 0xfd31000f;
    break;
  case 0x5b:
    local_c = hash % 0xfffffffb;
  }
  return local_c;
}