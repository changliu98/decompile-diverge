
static int sort_omegas(double v[4])
{
  int i;
  double w[4];

  i = 0;

  if (v[0] > v[1]) {
    w[0] = v[1];
    w[1] = v[0];
    i = 1;
  } else {
    w[0] = v[0];
    w[1] = v[1];
  }

  if (v[2] > v[3]) {
    w[2] = v[3];
    w[3] = v[2];
  } else {
    w[2] = v[2];
    w[3] = v[3];
  }

  if (w[0] > w[2]) {
    v[0] = w[2];
    v[1] = w[0];
    if (i == 0) {
      i = 4;
    }
  } else {
    v[0] = w[0];
    v[1] = w[2];
  }

  if (w[1] > w[3]) {
    v[3] = w[1];
    v[2] = w[3];
    if (i == 1) {
      i = 3;
    }
  } else {
    v[3] = w[3];
    v[2] = w[1];
    if (i == 1) {
      i = 5;
    }
  }

  if (v[1] > v[2]) {
    w[1] = v[1];
    v[1] = v[2];
    v[2] = w[1];
    if (i == 4) {
      i = 2;
    }
    if (i == 5) {
      i = 1;
    }
  } else {
    if (i == 4) {
      i = 1;
    }
    if (i == 5) {
      i = 2;
    }
  }
  return i;
}
