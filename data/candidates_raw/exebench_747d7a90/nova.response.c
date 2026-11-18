static int func0(const char *p, int *pi, int *sz){
  int i = 0;
  int c;
  while( (c = *(unsigned char*)p++)>=0x80 ){
    i = (i<<1)+c;
  }
  *pi = c;
  *sz = i+1;
  return c;
}