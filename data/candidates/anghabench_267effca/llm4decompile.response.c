uint32_t _ccv_sparse_matrix_index_for_hash(uint32_t hash, int prime_index)
{
 switch (prime_index)
 {
  case 0:
   return 0;
  case 1:
   return hash & 1;
  case 2:
   return hash % 3;
  case 3:
   return hash % 5;
  case 4:
   return hash % 7;
  case 5:
   return hash % 11;
  case 6:
   return hash % 13;
  case 7:
   return hash % 17;
  case 8:
   return hash % 23;
  case 9:
   return hash % 29;
  case 10:
   return hash % 37;
  case 11:
   return hash % 43;
  case 12:
   return hash % 53;
  case 13:
   return hash % 61;
  case 14:
   return hash % 71;
  case 15:
   return hash % 83;
  case 16:
   return hash % 97;
  case 17:
   return hash % 113;
  case 18:
   return hash % 131;
  case 19:
   return hash % 149;
  case 20:
   return hash % 167;
  case 21:
   return hash % 181;
  case 22:
   return hash % 197;
  case 23:
   return hash % 211;
  case 24:
   return hash % 229;
  case 25:
   return hash % 241;
  case 26:
   return hash % 257;
  case 27:
   return hash % 277;
  case 28:
   return hash % 293;
  case 29:
   return hash % 307;
  case 30:
   return hash % 323;
  case 31:
   return hash % 349;
  case 32:
   return hash % 367;
  case 33:
   return hash % 389;
  case 34:
   return hash % 409;
  case 35:
   return hash % 431;
  case 36:
   return hash % 457;
  case 37:
   return hash % 487;
  case 38:
   return hash % 509;
  case 39:
   return hash % 533;
  case 40:
   return hash % 563;
  case 41:
   return hash % 599;
  case 42:
   return hash % 629;
  case 43:
   return hash % 661;
  case 44:
   return hash % 691;
  case 45:
   return hash % 727;
  case 46:
   return hash % 751;
  case 47:
   return hash % 787;
  case 48:
   return hash % 823;
  case 49:
   return hash % 857;
  case 50:
   return hash % 899;
  case 51:
   return hash % 937;
  case 52:
   return hash % 983;
  case 53:
   return hash % 1031;
  case 54:
   return hash % 1073;
  case 55:
   return hash % 1123;
  case 56:
   return hash % 1159;
  case 57:
   return hash % 1201;
  case 58:
   return hash % 1249;
  case 59