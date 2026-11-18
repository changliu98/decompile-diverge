int nsvg__getArgsPerElement(char cmd)

{
  char cmd_local;
  int local_c;
  
  switch(cmd) {
  case 'A':
  case 'a':
    local_c = 7;
    break;
  default:
    local_c = -1;
    break;
  case 'C':
  case 'c':
    local_c = 6;
    break;
  case 'H':
  case 'V':
  case 'h':
  case 'v':
    local_c = 1;
    break;
  case 'L':
  case 'M':
  case 'T':
  case 'l':
  case 'm':
  case 't':
    local_c = 2;
    break;
  case 'Q':
  case 'S':
  case 'q':
  case 's':
    local_c = 4;
    break;
  case 'Z':
  case 'z':
    local_c = 0;
  }
  return local_c;
}