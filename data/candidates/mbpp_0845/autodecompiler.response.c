int func0(int n)
{
 double stirlingApprox = n * log10(n / 2.7182818284590452353602874713526624977572) + log10(2 * 3.141592653589793238462643383279502884197169399375105820974944592 * n / 2);
 int numDigit;

 if(n < 0)
  numDigit = 0;
 else if(n <= 1)
  numDigit = 1;
 else
  numDigit = (int)floor(stirlingApprox + 1);

 return numDigit;
}