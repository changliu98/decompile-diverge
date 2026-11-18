int
find(float xt, float *x, int n) {
  int il, im, itst, ihalf;


  if(xt <= x[0]) {
    return(0);
  }
  if(xt >= x[n-1]) {
    return(n-1);
  }
  ihalf = 0;
  il = 1;
  im = n;
  itst = im-il;

  while(itst > 1) {
    ihalf = (im + il) / 2;

    if(xt >= x[ihalf-1]) {

      il = ihalf;
    } else {

      im = ihalf;
    }
    itst = im - il;

  }
  return(il-1);
}