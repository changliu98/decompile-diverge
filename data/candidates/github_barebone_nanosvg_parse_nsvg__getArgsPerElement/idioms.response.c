int nsvg__getArgsPerElement(char c)
{
  int cmd;
  switch (c) {
    case 'a':
    case 'A':
      cmd = 7;
      break;
    case 'c':
    case 'C':
      cmd = 6;
      break;
    case 'h':
    case 'H':
    case 'v':
    case 'V':
      cmd = 1;
      break;
    case 'l':
    case 'L':
    case 'm':
    case 'M':
    case 't':
    case 'T':
      cmd = 2;
      break;
    case 's':
    case 'S':
    case 'q':
    case 'Q':
      cmd = 4;
      break;
    case 'z':
    case 'Z':
      cmd = 0;
      break;
    default:
      cmd = -1;
  }
  return cmd;
}