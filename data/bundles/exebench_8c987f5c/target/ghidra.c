char * minimum_size_type(int lwr,int upr,int *pnByte)

{
  int nByte;
  char *zType;
  int *pnByte_local;
  int upr_local;
  int lwr_local;
  
  zType = "int";
  nByte = 4;
  if (lwr < 0) {
    if ((lwr < -0x7f) || (0x7f < upr)) {
      if ((-0x8000 < lwr) && (upr < 0x7fff)) {
        zType = "short";
        nByte = 2;
      }
    }
    else {
      zType = "signed char";
      nByte = 1;
    }
  }
  else if (upr < 0x100) {
    zType = "unsigned char";
    nByte = 1;
  }
  else if (upr < 0xffff) {
    zType = "unsigned short int";
    nByte = 2;
  }
  else {
    zType = "unsigned int";
    nByte = 4;
  }
  if (pnByte != (int *)0x0) {
    *pnByte = nByte;
  }
  return zType;
}