
static void _Sort(int * p0, int * p1) {
  int temp;

  if (*p0 > *p1) {
    temp = *p0;
    *p0 = *p1;
    *p1 = temp;
  }
}
