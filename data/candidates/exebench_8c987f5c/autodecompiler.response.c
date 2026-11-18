static char *minimum_size_type(int min, int max, int *pnSize){
  char *zType = "unsigned int";
  int nType = 4;
  if( min>=0 ){
    if( max<256 ){
      zType = "unsigned char";
      nType = 1;
    }else if( max<65536 ){
      zType = "unsigned short int";
      nType = 2;
    }else{
      zType = "unsigned int";
      nType = 4;
    }
  }else if( min>-128 && max<128 ){
    zType = "signed char";
    nType = 1;
  }else if( min>-32768 && max<32768 ){
    zType = "short";
    nType = 2;
  }
  if( pnSize ) *pnSize = nType;
  return zType;
}