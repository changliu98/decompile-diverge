uint32_t __cdecl ccv_sparse_matrix_index_for_hash(const uint32_t hash, const int prime_index)
{
  uint32_t v3; // [rsp+14h] [rbp-4h]

  switch ( prime_index )
  {
    case 0:
      v3 = 0;
      break;
    case 1:
      v3 = hash & 1;
      break;
    case 2:
      v3 = hash % 3;
      break;
    case 3:
      v3 = hash % 5;
      break;
    case 4:
      v3 = hash % 7;
      break;
    case 5:
      v3 = hash % 0xB;
      break;
    case 6:
      v3 = hash % 0xD;
      break;
    case 7:
      v3 = hash % 0x11;
      break;
    case 8:
      v3 = hash % 0x17;
      break;
    case 9:
      v3 = hash % 0x1D;
      break;
    case 10:
      v3 = hash % 0x25;
      break;
    case 11:
      v3 = hash % 0x2F;
      break;
    case 12:
      v3 = hash % 0x3B;
      break;
    case 13:
      v3 = hash % 0x49;
      break;
    case 14:
      v3 = hash % 0x61;
      break;
    case 15:
      v3 = hash % 0x7F;
      break;
    case 16:
      v3 = hash % 0x97;
      break;
    case 17:
      v3 = hash % 0xC5;
      break;
    case 18:
      v3 = hash % 0xFB;
      break;
    case 19:
      v3 = hash % 0x139;
      break;
    case 20:
      v3 = hash % 0x18D;
      break;
    case 21:
      v3 = hash % 0x1F3;
      break;
    case 22:
      v3 = hash % 0x277;
      break;
    case 23:
      v3 = hash % 0x31D;
      break;
    case 24:
      v3 = hash % 0x3F1;
      break;
    case 25:
      v3 = hash % 0x4EB;
      break;
    case 26:
      v3 = hash % 0x63D;
      break;
    case 27:
      v3 = hash % 0x7DB;
      break;
    case 28:
      v3 = hash % 0x9EB;
      break;
    case 29:
      v3 = hash % 0xC83;
      break;
    case 30:
      v3 = hash % 0xFBB;
      break;
    case 31:
      v3 = hash % 0x13DF;
      break;
    case 32:
      v3 = hash % 0x1915;
      break;
    case 33:
      v3 = hash % 0x1F99;
      break;
    case 34:
      v3 = hash % 0x27D1;
      break;
    case 35:
      v3 = hash % 0x3235;
      break;
    case 36:
      v3 = hash % 0x3F41;
      break;
    case 37:
      v3 = hash % 0x4FAF;
      break;
    case 38:
      v3 = hash % 0x6475;
      break;
    case 39:
      v3 = hash % 0x7E91;
      break;
    case 40:
      v3 = hash % 0x9F77;
      break;
    case 41:
      v3 = hash % 0xC8ED;
      break;
    case 42:
      v3 = hash % 0xFD2B;
      break;
    case 43:
      v3 = hash % 0x13EF1;
      break;
    case 44:
      v3 = hash % 0x191DD;
      break;
    case 45:
      v3 = hash % 0x1FA47;
      break;
    case 46:
      v3 = hash % 0x27DEB;
      break;
    case 47:
      v3 = hash % 0x323BF;
      break;
    case 48:
      v3 = hash % 0x3F49D;
      break;
    case 49:
      v3 = hash % 0x4FBD9;
      break;
    case 50:
      v3 = hash % 0x64787;
      break;
    case 51:
      v3 = hash % 0x7E96D;
      break;
    case 52:
      v3 = hash % 0x9F7D3;
      break;
    case 53:
      v3 = hash % 0xC8F4D;
      break;
    case 54:
      v3 = hash % 0xFD303;
      break;
    case 55:
      v3 = hash % 0x13EFE9;
      break;
    case 56:
      v3 = hash % 0x191E9D;
      break;
    case 57:
      v3 = hash % 0x1FA611;
      break;
    case 58:
      v3 = hash % 0x27DFED;
      break;
    case 59:
      v3 = hash % 0x323D49;
      break;
    case 60:
      v3 = hash % 0x3F4C37;
      break;
    case 61:
      v3 = hash % 0x4FBFFB;
      break;
    case 62:
      v3 = hash % 0x647A97;
      break;
    case 63:
      v3 = hash % 0x7E9869;
      break;
    case 64:
      v3 = hash % 0x9F800F;
      break;
    case 65:
      v3 = hash % 0xC8F539;
      break;
    case 66:
      v3 = hash % 0xFD30E7;
      break;
    case 67:
      v3 = hash % 0x13F0031;
      break;
    case 68:
      v3 = hash % 0x191EA81;
      break;
    case 69:
      v3 = hash % 0x1FA61E9;
      break;
    case 70:
      v3 = hash % 0x27E0081;
      break;
    case 71:
      v3 = hash % 0x323D521;
      break;
    case 72:
      v3 = hash % 0x3F4C409;
      break;
    case 73:
      v3 = hash % 0x4FC012D;
      break;
    case 74:
      v3 = hash % 0x647AA43;
      break;
    case 75:
      v3 = hash % 0x7E987EF;
      break;
    case 76:
      v3 = hash % 0x9F80263;
      break;
    case 77:
      v3 = hash % 0xC8F5489;
      break;
    case 78:
      v3 = hash % 0xFD31009;
      break;
    case 79:
      v3 = hash % 0x13F004CB;
      break;
    case 80:
      v3 = hash % 0x191EA927;
      break;
    case 81:
      v3 = hash % 0x1FA61FFD;
      break;
    case 82:
      v3 = hash % 0x27E009B9;
      break;
    case 83:
      v3 = hash % 0x323D525B;
      break;
    case 84:
      v3 = hash % 0x3F4C3FF9;
      break;
    case 85:
      v3 = hash % 0x4FC01359;
      break;
    case 86:
      v3 = hash % 0x647AA4BF;
      break;
    case 87:
      v3 = hash % 0x7E987FF7;
      break;
    case 88:
      v3 = hash % 0x9F8026C9;
      break;
    case 89:
      v3 = hash % 0xC8F54987;
      break;
    case 90:
      v3 = hash % 0xFD31000F;
      break;
    case 91:
      v3 = hash % 0xFFFFFFFB;
      break;
    default:
      v3 = hash;
      break;
  }
  return v3;
}