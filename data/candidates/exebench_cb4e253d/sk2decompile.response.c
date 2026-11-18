long sort_omegas(double *omegas) {
  double om1, om2, om3, om4;
  long order = 0;
  if (omegas[0] > omegas[1]) {
    om1 = omegas[1];
    om2 = omegas[0];
    order = 1;
  } else {
    om1 = omegas[0];
    om2 = omegas[1];
  }
  if (omegas[2] > omegas[3]) {
    om3 = omegas[3];
    om4 = omegas[2];
  } else {
    om3 = omegas[2];
    om4 = omegas[3];
  }
  if (om1 > om3) {
    omegas[0] = om3;
    omegas[1] = om1;
    if (order == 0) order = 4;
  } else {
    omegas[0] = om1;
    omegas[1] = om3;
  }
  if (om2 > om4) {
    omegas[3] = om2;
    omegas[2] = om4;
    if (order == 1) order = 3;
  } else {
    omegas[3] = om4;
    omegas[2] = om2;
    if (order == 1) order = 5;
  }
  if (omegas[1] > omegas[2]) {
    om1 = omegas[1];
    omegas[1] = omegas[2];
    omegas[2] = om1;
    if (order == 4) order = 2;
    if (order == 5) order = 1;
  } else {
    if (order == 4) order = 1;
    if (order == 5) order = 2;
  }
  return order;
}