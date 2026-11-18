int divmod_test(struct divmod *d, unsigned long n)
{
 int ret;

 if (!n || d->m >= n) {
  ret = 1;
 } else {
  d->q = d->m / n;
  d->m = d->m % n;
  ret = 0;
 }

 return ret;
}