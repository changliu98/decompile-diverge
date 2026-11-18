Pointer to store the equivalent miles
void __cdecl measure(long *inches, int *inch, int *feet, int *yard, int *mile)
{
  // 63360 inches = 1 mile
  *inches = 63360LL;
  
  // Truncate the 64-bit value to 32-bit for the remaining calculations
  int total_inches = (int)*inches;
  
  *inch = total_inches;
  
  // 63360 * (1/12) = 5280 feet
  *feet = (int)(total_inches * 0.08333333333333333);
  
  // 63360 * (1/36) = 1760 yards
  *yard = (int)(total_inches * 0.02777777777777778);
  
  // 63360 * (1/63360) = 1 mile
  *mile = (int)(total_inches * 0.000015782828282828283);
}