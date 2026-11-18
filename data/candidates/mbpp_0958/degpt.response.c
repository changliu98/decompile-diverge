char * func0(int num)
{
  char *roman_symbols [13]; // Array to store Roman numeral symbols
  int roman_values [13];   // Array to store corresponding integer values
  
  // Copy Roman numeral values from global data table
  memcpy(roman_values,&DAT_00102010,0x34);
  // Copy Roman numeral symbols from global pointer table
  memcpy(roman_symbols,&PTR_DAT_00103d70,0x68);
  
  // Initialize the static roman_num buffer to empty string
  func0::roman_num[0] = '\0';
  int index = 0;
  
  // Loop while the number is greater than 0
  while (0 < num) {
    // Find the largest Roman numeral value that fits into the remaining number
    for (; roman_values[index] <= num; num = num - roman_values[index]) {
      // Append the corresponding Roman numeral symbol to the result
      strcat(func0::roman_num,roman_symbols[index]);
    }
    // Move to the next Roman numeral value/symbol pair
    index = index + 1;
  }
  // Return the constructed Roman numeral string
  return func0::roman_num;
}