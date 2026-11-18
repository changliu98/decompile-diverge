int sdsHdrSize(char type)

{
  char type_local;
  int local_c;
  
  switch(type & 7) {
  case 0:
    local_c = 1;
    break;
  case 1:
    local_c = 3;
    break;
  case 2:
    local_c = 5;
    break;
  case 3:
    local_c = 9;
    break;
  case 4:
    local_c = 0x11;
    break;
  default:
    local_c = 0;
  }
  return local_c;
}