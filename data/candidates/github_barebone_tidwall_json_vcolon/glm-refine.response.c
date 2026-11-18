#include <stdint.h>
#include <ctype.h>

// Encodes an error state while preserving the position (pos) where it failed
#define PARSE_ERROR(pos) (-(int64_t)((pos) + 1))

int64_t __cdecl skip_whitespace_and_colon(const uint8_t *json, int64_t len, int64_t i)
{
  int64_t pos = i;
  int ch;

  // Loop until we run out of characters
  while (pos < len)
  {
    ch = json[pos];
    
    // If it's not a whitespace character, we've found a significant token
    if (!isspace(ch))
    {
      // If the significant token is a colon, success. Return the next position.
      if (ch == ':')
        return pos + 1;
        
      // Otherwise, it's an invalid character (expected ':')
      break;
    }
    
    // Skip the whitespace
    pos++;
  }
  
  // Return error (either unexpected character or end of string)
  return PARSE_ERROR(pos);
}