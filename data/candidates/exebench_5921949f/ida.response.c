void __cdecl factorial(double *fact)
{
  int count; // [rsp+0h] [rbp-Ch]

  *fact = 1.0;
  for ( count = 0; count < 20; ++count )
    fact[count + 1] = (double)(count + 1) * fact[count];
}