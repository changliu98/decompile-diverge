static int func0(const unsigned char *z, sqlite3_int64 *pVal){
  sqlite3_int64 v = 0;
  int i, shift = 0;

  *pVal = z[0] & 0x7F;
  if( z[0]<0x80 ) return 1;
  for(i=1; z[i]>=0x80; i++){
    v |= (z[i] & 0x7F) << shift;
    shift += 7;
    *pVal |= v << (7*i);
    v = 0;
  }
  v |= z[i] << shift;
  *pVal |= v << (7*i);
  return i+1;
}