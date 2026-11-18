static int ccv_sparse_matrix_index_for_hash(int hash, int size) {
  switch (size) {
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
      return hash % 47;
    case 12:
      return hash % 59;
    case 13:
      return hash % 73;
    case 14:
      return hash % 97;
    case 15:
      return hash % 127;
    case 16:
      return hash % 151;
    case 17:
      return hash % 197;
    case 18:
      return hash % 251;
    case 19:
      return hash % 313;
    case 20:
      return hash % 397;
    case 21:
      return hash % 499;
    case 22:
      return hash % 631;
    case 23:
      return hash % 797;
    case 24:
      return hash % 1009;
    case 25:
      return hash % 1259;
    case 26:
      return hash % 1597;
    case 27:
      return hash % 2011;
    case 28:
      return hash % 2539;
    case 29:
      return hash % 3203;
    case 30:
      return hash % 4027;
    case 31:
      return hash % 5087;
    case 32:
      return hash % 6421;
    case 33:
      return hash % 8089;
    case 34:
      return hash % 10193;
    case 35:
      return hash % 12853;
    case 36:
      return hash % 16193;
    case 37:
      return hash % 20399;
    case 38:
      return hash % 25717;
    case 39:
      return hash % 32401;
    case 40:
      return hash % 40823;
    case 41:
      return hash % 51437;
    case 42:
      return hash % 64811;
    case 43:
      return hash % 81649;
    case 44:
      return hash % 102877;
    case 45:
      return hash % 129607;
    case 46:
      return hash % 163307;
    case 47:
      return hash % 205759;
    case 48:
      return hash % 259229;
    case 49:
      return hash % 326617;
    case 50:
      return hash % 411527;
    case 51:
      return hash % 518509;
    case 52:
      return hash % 653267;
    case 53:
      return hash % 823117;
    case 54:
      return hash % 1037059;
    case 55:
      return hash % 1306601;
    case 56:
      return hash % 1646237;
    case 57:
      return hash % 2074129;
    case 58:
      return hash % 2613229;
    case 59:
      return hash % 3292489;
    case 60:
      return hash % 4148279;
    case 61:
      return hash % 5226491;
    case 62:
      return hash % 6584983;
    case 63:
      return hash % 8296553;
    case 64:
      return hash % 10453007;
    case 65:
      return hash % 13169977;
    case 66:
      return hash % 16593127;
    case 67:
      return hash % 20906033;
    case 68:
      return hash % 26339969;
    case 69:
      return hash % 33186281;
    case 70:
      return hash % 41812097;
    case 71:
      return hash % 52679969;
    case 72:
      return hash % 66372617;
    case 73:
      return hash % 83624237;
    case 74:
      return hash % 105359939;
    case 75:
      return hash % 132745199;
    case 76:
      return hash % 167248483;
    case 77:
      return hash % 210719881;
    case 78:
      return hash % 265490441;
    case 79:
      return hash % 334496971;
    case 80:
      return hash % 421439783;
    case 81:
      return hash % 530980861;
    case 82:
      return hash % 668993977;
    case 83:
      return hash % 842879579;
    case 84:
      return hash % 1061961721;
    case 85:
      return hash % 1337987929;
    case 86:
      return hash % 1685759167;
    case 87:
      return hash % 2123923447;
    case 88:
      return hash % 2675975881;
    case 89:
      return hash % 3371518343;
    case 90:
      return hash % 4247846927;
    case 91:
      return hash % 4294967291;
    default:
      return hash;
  }
}