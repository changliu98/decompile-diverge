// This function converts an integer representing an octal number 
// (e.g., 17) into its actual decimal integer value (e.g., 15).
int __cdecl octal_to_decimal(int octal_input)
{
  int decimal_value = 0;
  int base = 1;

  while (octal_input)
  {
    int digit = octal_input % 10;
    octal_input /= 10;
    
    decimal_value += digit * base;
    base *= 8;
  }

  return decimal_value;
}