static int xrdp_wm_parse_domain_information(const char *zName, int nName, int bDelete, char *zNew){
  int nNew = 0;
  int n;
  memset(zNew, 0, 256);
  if( zName[0]=='_' ){
    n = sqlite3Strlen30(zName+1);
    if( n>0 ){
      if( bDelete ){
        char zC[3];
        memset(zC, 0, sizeof(zC));
        memcpy(zC, &zName[n+1], 1);
        n = atoi(zC);
        if( n>0 && n<nName ) nNew = n;
      }else{
        memcpy(&zNew[1], &zName[1], n);
      }
    }
  }
  if( nNew==0 ){
    memcpy(&zNew[1], &zName[1], 255);
  }
  return nNew;
}