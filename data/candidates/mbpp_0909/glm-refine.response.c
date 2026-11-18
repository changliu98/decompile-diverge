#include <stdio.h>
#include <string.h>

// Helper function to represent the inline string reversal logic
void reverse_string(char* str, int len) {
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Finds the largest positive integer strictly less than 'num' that is a palindrome.
// Returns the palindrome if found, otherwise returns 0.
int __cdecl find_largest_palindrome_less_than(int num)
{
  char str[12];       // Buffer to hold the string representation of the integer (max 10 digits + sign + null)
  char reversed[12];  // Buffer to hold the reversed string
  
  // Iterate downwards from (num - 1) to 1
  for (int current = num - 1; current > 0; --current)
  {
    // Convert the current integer to a string
    sprintf(str, "%d", current);
    
    // Copy the string to reverse it
    strcpy(reversed, str);
    int len = strlen(reversed);
    
    // Reverse the string in-place
    reverse_string(reversed, len);
    
    // Check if the original string and the reversed string are identical
    if (strcmp(str, reversed) == 0)
    {
      return current; // Found the largest palindrome
    }
  }
  
  return 0; // No palindrome found in the given range
}