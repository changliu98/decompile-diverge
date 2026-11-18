#include <stdint.h>

// The function subtracts array 'b' from array 'a' element-wise, 
// propagating a borrow across the elements, and stores the result in 'out'.
// The arrays represent 32-byte (256-bit) integers, likely in little-endian byte order.
void __cdecl sub_256bit(unsigned int *out, const unsigned int *a, const unsigned int *b)
{
  unsigned int carry; // Replaces 'u' / 'ua' - acts as both borrow and intermediate sum
  unsigned int i;     // Loop counter

  // 218 is the initial borrow/carry value. 
  // 65280 (0xFF00) is used to handle underflow during subtraction.
  // When a[j] - b[j] underflows, (a[j] - b[j] + 0xFF00) >> 8 yields 0xFF (255), 
  // which effectively acts as a -1 borrow for the next iteration.
  carry = 218;
  
  for (i = 0; i < 31; ++i)
  {
    // Add the current carry and 0xFF00, then subtract b[i] from a[i]
    carry += a[i] + 65280 - b[i];
    
    // Store the lowest 8 bits of the result
    out[i] = (uint8_t)carry;
    
    // Shift right by 8 to extract the borrow/carry for the next iteration
    carry >>= 8;
  }
  
  // Process the final element (index 31) without truncating to 8 bits
  out[31] = carry + a[31] - b[31];
}