long sort_omegas(double *v)

{
  double dVar1;
  bool bVar2;
  bool bVar3;
  double w [4];
  long i;
  double *v_local;
  
  dVar1 = *v;
  bVar2 = dVar1 == v[1];
  bVar3 = dVar1 < v[1];
  if (bVar3 || bVar2) {
    w[0] = *v;
    w[1] = v[1];
  }
  else {
    w[0] = v[1];
    w[1] = *v;
  }
  i = (long)(!bVar3 && !bVar2);
  if (v[2] < v[3] || v[2] == v[3]) {
    w[2] = v[2];
    w[3] = v[3];
  }
  else {
    w[2] = v[3];
    w[3] = v[2];
  }
  if (w[0] <= w[2]) {
    *v = w[0];
    v[1] = w[2];
  }
  else {
    *v = w[2];
    v[1] = w[0];
    if (i == 0) {
      i = 4;
    }
  }
  if (w[1] <= w[3]) {
    v[3] = w[3];
    v[2] = w[1];
    if (i == 1) {
      i = 5;
    }
  }
  else {
    v[3] = w[1];
    v[2] = w[3];
    if (i == 1) {
      i = 3;
    }
  }
  if (v[1] < v[2] || v[1] == v[2]) {
    if (i == 4) {
      i = 1;
    }
    if (i == 5) {
      i = 2;
    }
  }
  else {
    dVar1 = v[1];
    v[1] = v[2];
    v[2] = dVar1;
    if (i == 4) {
      i = 2;
    }
    if (i == 5) {
      i = 1;
    }
  }
  return i;
}