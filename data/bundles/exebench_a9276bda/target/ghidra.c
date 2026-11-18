char * intToString(char *buff,uint val)

{
  int i;
  uint val_local;
  char *buff_local;
  
  buff[9] = '\0';
  val_local = val;
  for (i = 8; -1 < i; i = i + -1) {
    buff[i] = (char)(val_local % 10) + '0';
    val_local = val_local / 10;
    if (val_local == 0) break;
  }
  return buff + i;
}