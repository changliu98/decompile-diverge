int __cdecl nsvg__getArgsPerElement(char cmd)
{
  int v2; // [rsp+Ch] [rbp-4h]

  switch ( cmd )
  {
    case 'A':
    case 'a':
      v2 = 7;
      break;
    case 'C':
    case 'c':
      v2 = 6;
      break;
    case 'H':
    case 'V':
    case 'h':
    case 'v':
      v2 = 1;
      break;
    case 'L':
    case 'M':
    case 'T':
    case 'l':
    case 'm':
    case 't':
      v2 = 2;
      break;
    case 'Q':
    case 'S':
    case 'q':
    case 's':
      v2 = 4;
      break;
    case 'Z':
    case 'z':
      v2 = 0;
      break;
    default:
      v2 = -1;
      break;
  }
  return v2;
}