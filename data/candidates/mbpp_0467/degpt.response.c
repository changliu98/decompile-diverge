int func0(int decimalNumber)
{
  int octalResult = 0; // Variable to store the resulting octal number
  int placeMultiplier = 1; // Multiplier to place digits in correct positions (1, 10, 100, etc.)
  for (int currentDecimal = decimalNumber; currentDecimal != 0; currentDecimal /= 8) {
    octalResult += (currentDecimal % 8) * placeMultiplier; // Extract last octal digit and add to result at correct position
    placeMultiplier *= 10; // Move to the next decimal place for the next digit
  }
  return octalResult; // Return the converted octal number
}