int stringToInt(uint *val,char *buff)

{
  char *buff_local;
  uint *val_local;
  
  *val = 0;
  buff_local = buff;
  while( true ) {
    if (*buff_local == '\0') {
      return 0;
    }
    if ((*buff_local < '0') || ('9' < *buff_local)) break;
    *val = (*val * 10 + (int)*buff_local) - 0x30;
    buff_local = buff_local + 1;
  }
  return -1;
}