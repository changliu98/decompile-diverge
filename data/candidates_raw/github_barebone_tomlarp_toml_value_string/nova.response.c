static int func0(const char *zDate, DateTime *p){
  int Y, M, D, neg;

  p->iJD = (sqlite3_int64)0;
  zDate += 10;
  if( zDate[0]==0 ){
    p->rawSuffix = -1;
    return -1;
  }
  neg = (*zDate=='-');
  if( neg ) zDate++;
  if( getDigits(zDate, 4)!=4 ) return -1;
  Y = atoi(zDate);
  zDate += 4;
  if( getDigits(zDate, 2)!=2 ) return -1;
  M = atoi(zDate);
  zDate += 2;
  D = atoi(zDate);
  p->iJD = julianDay(Y, M, D, neg);
  if( p->iJD==0 ){
    return -1;
  }
  return 0;
}