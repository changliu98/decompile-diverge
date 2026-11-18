void MassRelease(double *Mass, double *MassIn, double *MassOut,
                 double *MassOut2) {
  double MassIn_min;
  double MassIn_max;
  double MassOut_temp;
  if (*Mass > 0.005) {
    MassIn_min = 0.1 * (*Mass);
    MassIn_max = 0.17 * (*Mass);
    if (*MassIn >= MassIn_min) {
      *MassOut2 += MassIn_min;
      *Mass -= MassIn_min;
      *MassIn -= MassIn_min;
      if (*Mass < 0.005) {
        MassOut_temp = 0.0;
      } else {
        MassOut_temp = (*Mass - 0.005);
        if (MassOut_temp > MassIn_max) {
          MassOut_temp = MassIn_max;
        }
      }
      *MassOut += MassOut_temp;
      *Mass -= MassOut_temp;
      MassRelease(Mass, MassIn, MassOut, MassOut2);
    } else {
      if (*Mass > *MassIn) {
        MassOut_temp = *MassIn;
      } else {
        MassOut_temp = *Mass;
      }
      *MassOut2 += MassOut_temp;
      *Mass -= MassOut_temp;
      *MassIn = 0.0;
    }
  } else {
    if (*Mass > *MassIn) {
      MassOut_temp = *MassIn;
    } else {
      MassOut_temp = *Mass;
    }
    *MassOut2 += MassOut_temp;
    *Mass -= MassOut_temp;
    *MassIn = 0.0;
  }
  return;
}