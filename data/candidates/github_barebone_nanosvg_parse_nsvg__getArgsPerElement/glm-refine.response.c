int __cdecl nsvg__getArgsPerElement(char cmd)
{
  switch ( cmd )
  {
    case 'A':
    case 'a':
      return 7;
    case 'C':
    case 'c':
      return 6;
    case 'H':
    case 'V':
    case 'h':
    case 'v':
      return 1;
    case 'L':
    case 'M':
    case 'T':
    case 'l':
    case 'm':
    case 't':
      return 2;
    case 'Q':
    case 'S':
    case 'q':
    case 's':
      return 4;
    case 'Z':
    case 'z':
      return 0;
    default:
      return -1;
  }
}