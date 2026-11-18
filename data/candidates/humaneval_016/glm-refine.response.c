#include <ctype.h>

int __cdecl count_unique_alpha_chars(const char *str)
{
  char lower_ch;
  int index;
  int char_map[256];
  int count;
  const char *current_str;

  current_str = str;
  count = 0;
  
  // Initialize the character frequency/seen map to all zeros
  memset(char_map, 0, sizeof(char_map));
  
  for (index = 0; current_str[index] != '\0'; ++index)
  {
    // Convert character to lowercase
    lower_ch = tolower((unsigned char)current_str[index]);
    
    // Check if the character hasn't been seen yet and is an alphabetic letter.
    // (*__ctype_b_loc())[(unsigned char)lower_ch] & 0x400 is the glibc internal 
    // bit-mask check for isalpha(lower_ch).
    if (!char_map[(unsigned char)lower_ch] && isalpha(lower_ch))
    {
      char_map[(unsigned char)lower_ch] = 1;
      ++count;
    }
  }
  
  return count;
}