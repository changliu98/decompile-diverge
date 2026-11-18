char *minimum_size_type(int lwr, int upr, int *pnByte){
  char *zType = "int";
  int nByte = 4;
  if( lwr >= 0 ){
    if( upr <= 0xff ){
      zType = "unsigned char";
      nByte = 1;
    }else if( upr <= 0xffff ){
      zType = "unsigned short int";
      nByte = 2;
    }else{
      zType = "unsigned int";
      nByte = 4;
    }
  }else{
    if( lwr >= -0x7f && upr <= 0x7f ){
      zType = "signed char";
      nByte = 1;
    }else if( lwr >= -0x7fff && upr <= 0x7fff ){
      zType = "short";
      nByte = 2;
    }
  }
  if( pnByte ) *pnByte = nByte;
  return zType;
}