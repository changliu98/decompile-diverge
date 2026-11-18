int LI_ltostr(char *buf,long val)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int len;
  char *end;
  char swap;
  long val_local;
  char *buf_local;
  
  len = 1;
  val_local = val;
  buf_local = buf;
  if (val < 0) {
    len = 2;
    buf_local = buf + 1;
    *buf = '-';
    val_local = -val;
  }
  end = buf_local;
  for (; 9 < val_local; val_local = val_local / 10) {
    *end = (char)(val_local % 10) + '0';
    end = end + 1;
  }
  *end = (char)val_local + '0';
  end[1] = '\0';
  iVar3 = (int)buf_local;
  iVar2 = (int)end;
  for (; buf_local < end; buf_local = buf_local + 1) {
    cVar1 = *end;
    *end = *buf_local;
    *buf_local = cVar1;
    end = end + -1;
  }
  return len + (iVar2 - iVar3);
}