static char *func0(const char *z){
  int n = (int)strlen(z);
  char *zRet;
  int i, nDigit, nUpper;

  if( n<6 ){
    zRet = "BAD_PASS";
  }else if(!(z[0]>='A' && z[0]<='Z') &&!(z[0]>='a' && z[0]<='z') ){
    zRet = "BAD_PASS";
  }else{
    const char *zT = &z[n-2];
    if( memcmp(zT, "er", 2)==0 || memcmp(zT, "ing", 3)==0
     || memcmp(zT, "ed", 2)==0 ){
      zRet = "STRONG_PASS";
    }else{
      nDigit = nUpper = 0;
      for(i=0; i<n; i++){
        if( z[i]>='0' && z[i]<='9' ){
          nDigit++;
        }
        if( z[i]=='.' ){
          nUpper++;
        }
      }
      if( nDigit<4 || nUpper!=1 ){
        zRet = "WEAK_PASS";
      }else{
        zRet = "MEDIUM_PASS";
      }
    }
  }
  return zRet;
}