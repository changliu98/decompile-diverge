void kf_factor(int n,int *facbuf)

{
  int *piVar1;
  double dVar2;
  double floor_sqrt;
  int p;
  int *facbuf_local;
  int n_local;
  
  p = 4;
  dVar2 = sqrt((double)n);
  dVar2 = floor(dVar2);
  n_local = n;
  facbuf_local = facbuf;
  do {
    while (n_local % p != 0) {
      if (p == 2) {
        p = 3;
      }
      else if (p == 4) {
        p = 2;
      }
      else {
        p = p + 2;
      }
      if (dVar2 < (double)p) {
        p = n_local;
      }
    }
    n_local = n_local / p;
    piVar1 = facbuf_local + 1;
    *facbuf_local = p;
    facbuf_local = facbuf_local + 2;
    *piVar1 = n_local;
  } while (1 < n_local);
  return;
}