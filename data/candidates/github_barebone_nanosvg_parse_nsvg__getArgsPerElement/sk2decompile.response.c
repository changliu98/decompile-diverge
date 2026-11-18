static int nsvg__getArgsPerElement(char c) {
  int n;
  switch (c) {
    case 'M':
    case 'L':
    case 'T':
    case 'l':
    case 'm':
    case 't':
      n = 2;
      break;
    case 'Q':
    case 'S':
    case 'q':
    case 's':
      n = 4;
      break;
    case 'C':
    case 'c':
      n = 6;
      break;
    case 'A':
    case 'a':
      n = 7;
      break;
    case 'H':
    case 'V':
    case 'h':
    case 'v':
      n = 1;
      break;
    case 'Z':
    case 'z':
      n = 0;
      break;
    default:
      n = -1;
      break;
  }
  return n;
}