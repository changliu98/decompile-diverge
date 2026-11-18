int __cdecl func0(char *str)
{
  int sum = 0;
  
  // Calculate the sum of 1-based alphabet positions for each character
  for (int i = 0; str[i]; ++i)
    sum += str[i] - 'a' + 1;

  int mod = sum % 26;
  
  // Map the modulo result back to a lowercase letter ('a' through 'z')
  // If mod is 0, it maps to 'z' (122). Otherwise, it maps to 'a' through 'y'.
  return mod ? mod + 'a' - 1 : 'z';
}