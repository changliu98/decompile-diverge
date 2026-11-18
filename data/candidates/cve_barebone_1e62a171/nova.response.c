static int name_len(
  const u8 *a, const u8 *b, const u8 *const end
){
  int dflt = -1;
  const u8 *p = b;
  if( b>=end ){
    
    return dflt;
  }
  if( a[-1]<=(a[0]-1) ){
    
    while( p<end && p<a-1 ){
      u8 c = *p++;
      if( (c&0xc0)==0xc0 ){
        return 2;
      }
      if( c==0 ){
        while( p<end ){
          if( p>=a ) return dflt;
          if( *p++ ) return p-b;
        }
        return dflt;
      }
    }
  }
  return p-b;
}