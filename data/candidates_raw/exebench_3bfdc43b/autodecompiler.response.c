static void
fixup(int *ip, int *jp, int base)
{
 int k;

 if (*jp < 0) {
  k = (-*jp - 1) / base + 1;
  *ip -= k;
  *jp += k * base;
 }
 if (*jp >= base) {
  k = *jp / base;
  *ip += k;
  *jp -= k * base;
 }
}