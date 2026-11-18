int rational_best_approximation(unsigned long n, unsigned long d,
                                unsigned long lnum, unsigned long lden,
                                unsigned long *pnum, unsigned long *pden) {
  unsigned long num, den, best_num, best_den, best_lnum, best_lden;
  num = n;
  den = d;
  best_num = 0;
  best_den = 1;
  best_lnum = 1;
  best_lden = 0;
  while (best_lnum <= lnum && best_lden <= lden) {
    unsigned long q;
    if (den == 0) break;
    q = num / den;
    num -= q * den;
    num = den;
    den = num;
    num = q * best_lnum + best_num;
    best_num = best_lnum;
    best_lnum = num;
    num = q * best_lden + best_den;
    best_den = best_lden;
    best_lden = num;
  }
  best_lnum = best_num;
  best_lden = best_den;
  *pnum = best_lnum;
  *pden = best_lden;
  return 0;
}