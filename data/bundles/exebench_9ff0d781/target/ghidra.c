int get_hex(char *buf,uint *num)

{
  bool bVar1;
  int done;
  int cpos;
  uint *num_local;
  char *buf_local;
  
  cpos = 0;
  bVar1 = false;
  *num = 0;
  while (!bVar1) {
    if ((buf[cpos] < '0') || ('9' < buf[cpos])) {
      if ((buf[cpos] < 'A') || ('F' < buf[cpos])) {
        if ((buf[cpos] < 'a') || ('f' < buf[cpos])) {
          bVar1 = true;
        }
        else {
          *num = *num << 4;
          *num = (*num + (int)buf[cpos]) - 0x57;
        }
      }
      else {
        *num = *num << 4;
        *num = (*num + (int)buf[cpos]) - 0x37;
      }
    }
    else {
      *num = *num << 4;
      *num = (*num + (int)buf[cpos]) - 0x30;
    }
    if (!bVar1) {
      cpos = cpos + 1;
    }
    if (7 < cpos) {
      bVar1 = true;
    }
  }
  return cpos;
}