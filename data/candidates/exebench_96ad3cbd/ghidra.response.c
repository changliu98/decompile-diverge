char * maybeint(char *q,int *dst)

{
  bool bVar1;
  int num;
  int *dst_local;
  char *q_local;
  
  if ((*q < '0') || ('9' < *q)) {
    *dst = 0;
    q_local = q;
  }
  else {
    num = 0;
    q_local = q;
    while( true ) {
      bVar1 = false;
      if ('/' < *q_local) {
        bVar1 = *q_local < ':';
      }
      if (!bVar1) break;
      num = num * 10 + *q_local + -0x30;
      q_local = q_local + 1;
    }
    *dst = num;
  }
  return q_local;
}