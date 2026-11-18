char * _getbase(char *p,int *basep)

{
  int *basep_local;
  char *p_local;
  char *local_10;
  
  if (*p == '0') {
    switch(p[1]) {
    case 'n':
    case 't':
      *basep = 10;
      break;
    case 'o':
      *basep = 8;
      break;
    default:
      *basep = 10;
      return p;
    case 'x':
      *basep = 0x10;
    }
    local_10 = p + 2;
  }
  else {
    *basep = 10;
    local_10 = p;
  }
  return local_10;
}