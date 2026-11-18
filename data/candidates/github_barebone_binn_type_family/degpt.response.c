int type_family(int input_type)
{
  // If type is 0, return family 0xf1
  if (input_type == 0) {
    return 0xf1;
  }
  // Check if type falls within ranges [0x20, 0x21], [0x40, 0x41], or [0x60, 0x61]
  // Using unsigned subtraction to handle wrap-around for range checks
  if (((input_type - 0x20U < 2) || (input_type - 0x40U < 2)) || (input_type - 0x60U < 2)) {
    return 0xf2;
  }
  // If type is 0x62, skip to the final return 0xf3
  if (input_type != 0x62) {
    // Check if type falls within range [0x80, 0x81]
    if (input_type - 0x80U < 2) return 0xf2;
    // If type is not 0x82, proceed with further checks
    if (input_type != 0x82) {
      // If type is 0x83, return family 0xf4
      if (input_type == 0x83) {
        return 0xf4;
      }
      // If type is 0xa0, return family 0xf4
      if (input_type == 0xa0) {
        return 0xf4;
      }
      // Check if type falls within range [0xa1, 0xa4]
      if (input_type - 0xa1U < 4) {
        return 0xf4;
      }
      // Check if type is greater than 0xa6 (i.e., type - 0xa6U > 1)
      if (1 < input_type - 0xa6U) {
        // If type is not 0xc0, proceed with further checks
        if (input_type != 0xc0) {
          // Check if type falls within range [0xe0, 0xe2]
          if (input_type - 0xe0U < 3) {
            return 0xf7;
          }
          // Check if type falls within range [0xb001, 0xb005]
          if (input_type - 0xb001U < 5) {
            return 0xf4;
          }
          // Check if type is greater than 0xd003 (i.e., type - 0xd001U > 3)
          if (3 < input_type - 0xd001U) {
            // If type is exactly 0x80061, return family 0xf6
            if (input_type == 0x80061) {
              return 0xf6;
            }
            // Otherwise, return 0
            return 0;
          }
        }
        // If type is 0xc0 or falls in the range checked above, return family 0xf5
        return 0xf5;
      }
    }
  }
  // Default return value for type 0x62 or other unmatched cases
  return 0xf3;
}