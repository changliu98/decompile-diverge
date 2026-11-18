unsigned int _ccv_sparse_matrix_index_for_hash(unsigned int hash, int prime_index)
{
  unsigned int prime = 0;
  switch (prime_index)
  {
    case 0:
      prime = 0;
      break;
    case 1:
      prime = hash & 1;
      break;
    case 2:
      prime = hash % 3;
      break;
    case 3:
      prime = hash % 5;
      break;
    case 4:
      prime = hash % 7;
      break;
    case 5:
      prime = hash % 11;
      break;
    case 6:
      prime = hash % 13;
      break;
    case 7:
      prime = hash % 17;
      break;
    case 8:
      prime = hash % 19;
      break;
    case 9:
      prime = hash % 25;
      break;
    case 10:
      prime = hash % 29;
      break;
    case 11:
      prime = hash % 37;
      break;
    case 12:
      prime = hash % 47;
      break;
    case 13:
      prime = hash % 61;
      break;
    case 14:
      prime = hash % 79;
      break;
    case 15:
      prime = hash % 127;
      break;
    case 16:
      prime = hash % 163;
      break;
    case 17:
      prime = hash % 223;
      break;
    case 18:
      prime = hash % 281;
      break;
    case 19:
      prime = hash % 353;
      break;
    case 20:
      prime = hash % 421;
      break;
    case 21:
      prime = hash % 521;
      break;
    case 22:
      prime = hash % 631;
      break;
    case 23:
      prime = hash % 761;
      break;
    case 24:
      prime = hash % 919;
      break;
    case 25:
      prime = hash % 1123;
      break;
    case 26:
      prime = hash % 1351;
      break;
    case 27:
      prime = hash % 1621;
      break;
    case 28:
      prime = hash % 1931;
      break;
    case 29:
      prime = hash % 2293;
      break;
    case 30:
      prime = hash % 2717;
      break;
    case 31:
      prime = hash % 3203;
      break;
    case 32:
      prime = hash % 3779;
      break;
    case 33:
      prime = hash % 4441;
      break;
    case 34:
      prime = hash % 5221;
      break;
    case 35:
      prime = hash % 6193;
      break;
    case 36:
      prime = hash % 7361;
      break;
    case 37:
      prime = hash % 8729;
      break;
    case 38:
      prime = hash % 10301;
      break;
    case 39:
      prime = hash % 12193;
      break;
    case 40:
      prime = hash % 14411;
      break;
    case 41:
      prime = hash % 17011;
      break;
    case 42:
      prime = hash % 20031;
      break;
    case 43:
      prime = hash % 23553;
      break;
    case 44:
      prime = hash % 27641;
      break;