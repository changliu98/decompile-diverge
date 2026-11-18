// Recursive function to multiply x by y using addition
int multiply(int multiplicand, int multiplier)
{
  // Handle negative multiplier: negate result of recursive call with positive y
  if (multiplier < 0) {
    return -multiply(multiplicand, -multiplier);
  }
  // Base case: any number multiplied by 0 is 0
  else if (multiplier == 0) {
    return 0;
  }
  else {
    // Base case: any number multiplied by 1 is the number itself
    if (multiplier == 1) {
      return multiplicand;
    }
    // Recursive step: x * y = x + x * (y - 1)
    return multiplicand + multiply(multiplicand, multiplier - 1);
  }
}