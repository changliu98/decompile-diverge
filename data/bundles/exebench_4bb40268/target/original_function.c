void check_int(int *x,int *y,char* ret) {
  *ret = ((char*)y)-((char*)x) == sizeof(*x) ? 't' : 'f';
}