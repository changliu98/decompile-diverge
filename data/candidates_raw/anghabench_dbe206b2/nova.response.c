int func0(unsigned char *p, int *piType){
  int i, j;
  if( p[0]==0xF ){
    *piType = p[0];
    return 2;
  }
  *piType = p[0];
  for(i=1;;i++){
    if( p[i]>=0xF ){
      return i+1;
    }
  }
  assert(0);
  return 0;
}