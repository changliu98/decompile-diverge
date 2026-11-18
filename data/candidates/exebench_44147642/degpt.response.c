void uppercase(int *char_ptr)
{
  // Convert lowercase letters 'a'-'z' to uppercase by subtracting 0x20 (32)
  // The condition checks if the character is in the range 'a'-'z'
  // 'a' is 0x61, 'z' is 0x7a
  // The ranges are split to handle the ASCII values:
  // 0x61-0x69: 'a'-'i'
  // 0x6b-0x72: 'k'-'r'
  // 0x74-0x7a: 't'-'z'
  // Note: The original condition has a bug - it misses 'j' (0x6a), 's' (0x73), and 'u'-'w' are not covered correctly
  // Correct range for lowercase 'a'-'z' is 0x61 to 0x7a
  if (((*char_ptr > 0x60 && *char_ptr < 0x6a) || (*char_ptr > 0x69 && *char_ptr < 0x73)) ||
     (*char_ptr > 0x72 && *char_ptr < 0x7b)) {
    *char_ptr += -0x20;
  }
}