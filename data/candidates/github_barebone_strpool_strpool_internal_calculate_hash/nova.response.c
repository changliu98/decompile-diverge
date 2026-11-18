static unsigned int strpool_internal_calculate_hash(const char *z, int n, int iNull){
  unsigned int h = 5381;
  if( iNull ){
    int i;
    for(i=0; i<n; i++){
      char x = z[i];
      if( x>'z' || x<'a' ) x = (char)(x & 0x7F);
      h = (h<<5) + h + (unsigned int)x;
    }
  }else{
    int i;
    for(i=0; i<n; i++){
      char x = z[i];
      h = (h<<5) + h + (unsigned int)x;
    }
  }
  if( h==0 ) h = 1;
  return h;
}