void __cdecl calcular_escala(double fmin, double fmax, double favg, double *m, double *b)
{
  // COERCE_DOUBLE(*(_QWORD *)&fmax ^ 0x8000000000000000LL) is the IDA Pro way 
  // to represent the unary minus operation on a double (-fmax).
  if ( fmin <= (favg * 1.2 - fmax) / 0.2 )
  {
    if ( favg == fmin )
    {
      *m = 1.0;
      *b = 0.0;
    }
    else
    {
      *m = favg / (favg - fmin);
      *b = -fmin * favg / (favg - fmin);
    }
  }
  else
  {
    *m = 0.2 * favg / (fmax - favg);
    *b = favg * (fmax - favg * 1.2) / (fmax - favg);
  }
}