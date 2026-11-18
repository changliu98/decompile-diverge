void calcular_escala(double fmin,double fmax,double favg,double *m,double *b)

{
  double delta;
  double *b_local;
  double *m_local;
  double favg_local;
  double fmax_local;
  double fmin_local;
  
  if (fmin <= (favg * DAT_00102010 + -fmax) / DAT_00102008) {
    if ((favg != fmin) || (NAN(favg) || NAN(fmin))) {
      *m = favg / (favg - fmin);
      *b = (-fmin * favg) / (favg - fmin);
    }
    else {
      *m = DAT_00102018;
      *b = 0.0;
    }
  }
  else {
    *m = (DAT_00102008 * favg) / (fmax - favg);
    *b = favg * ((favg * DAT_00102020 + fmax) / (fmax - favg));
  }
  return;
}