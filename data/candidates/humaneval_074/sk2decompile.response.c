char **func0(char **a, int na, char **b, int nb) {
  int la = 0, lb = 0, i;
  for (i = 0; i < na; i++) {
    la += strlen(a[i]);
  }
  for (i = 0; i < nb; i++) {
    lb += strlen(b[i]);
  }
  if (la < lb) {
    return a;
  } else if (la > lb) {
    return b;
  } else {
    return a;
  }
}