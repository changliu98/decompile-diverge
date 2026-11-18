void __cdecl calcular_escala(double fmin, double fmax, double favg, double *m, double *b)
{
  if ( fmin <= (favg * 1.2 + COERCE_DOUBLE(*(_QWORD *)&fmax ^ 0x8000000000000000LL)) / 0.2 )
  {
    if ( favg == fmin )
    {
      *m = 1.0;
      *b = 0.0;
    }
    else
    {
      *m = favg / (favg - fmin);
      *b = COERCE_DOUBLE(*(_QWORD *)&fmin ^ 0x8000000000000000LL) * favg / (favg - fmin);
    }
  }
  else
  {
    *m = 0.2 * favg / (fmax - favg);
    *b = favg * ((favg * -1.2 + fmax) / (fmax - favg));
  }
}