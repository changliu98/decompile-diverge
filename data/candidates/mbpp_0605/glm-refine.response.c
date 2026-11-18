bool __cdecl is_prime(int number)
{
  int divisor; 

  if (number < 1)
    return false;
    
  for (divisor = 2; divisor <= number / 2; ++divisor)
  {
    if (number % divisor == 0)
      return false;
  }
  
  return true;
}