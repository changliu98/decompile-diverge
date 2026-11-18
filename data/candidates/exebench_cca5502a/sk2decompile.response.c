int modpars_to_struct(float *par, int *ipar, int *npar, float *parval,
                      float *parvals) {
  if (*ipar == 1) {
    *par = *parval;
    return 1;
  } else if (*ipar > *npar) {
    *par = *parval;
    *npar = *ipar;
    parvals[*ipar - 2] = *parval;
    return 1;
  } else if (*ipar > 1) {
    *par = parvals[*ipar - 2];
  }
  return 0;
}