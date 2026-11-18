double ran1 ( long *idum ) {






  int j;
  long k;
  double temp;
  static long iy=0;
  static long iv[32];

  if ( (*idum <= 0) || (iy == 0) ) {
    if (-(*idum) < 1 ) {
      *idum = 1 ;
    } else {
      *idum = -(*idum);
    }
    for(j=32 +7;j>=0;j--) {
      k = *idum/127773;
      *idum = 16807*(*idum-k*127773)-2836*k;
      if(*idum < 0) *idum += 2147483647;
      if(j < 32) iv[j] = *idum;
    }
    iy = iv[0];
  }
  k = *idum / 127773;
  *idum = 16807 * ( *idum - k * 127773 ) - 2836 * k ;
  if( *idum < 0 ) *idum += 2147483647 ;
  j = iy / (1+(2147483647 -1)/32) ;
  iy = iv[j] ;
  iv[j] = *idum;
  if ( (temp = (1.0/2147483647) * iy ) > (1.0-(1.2E-07)) ) {
    return (1.0-(1.2E-07)) ;
  } else {
    return temp ;
  }
}