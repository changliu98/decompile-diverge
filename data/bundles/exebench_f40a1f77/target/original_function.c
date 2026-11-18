static void get_bits_exp(double x, double *a, int *n) {
  double t,t2;
  unsigned int *u,*v;

  t2 = t = x;


     u=(unsigned int *) &t2;
     v=u+1;


     v=(unsigned int *) &t2;
     u=v+1;


  *u = ((*u) & 0x7ff00000);
  if (*u == 0) {
    t2 = t2*1024*1024*1024*1024*1024*1024;
    *u = ((*u) & 0x7ff00000);
    *v = 0;
    *n = (((*u)>>20) - 1023)-60;
    t2 = t2/(1024.0*1024*1024*1024*1024*1024);
    *a = t/t2;
  }
  else {
    *v = 0;
    *n = (((*u)>>20) - 1023);
    *a = t/t2;
  }
}