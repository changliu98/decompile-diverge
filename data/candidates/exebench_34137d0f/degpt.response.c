int sha_init(int *hash_values)
{
  // Initialize the first hash value (A) with the first 32 bits of the fractional part of the square root of 2
  *hash_values = 0x67452301;
  // Initialize the second hash value (B) with the first 32 bits of the fractional part of the square root of 3
  hash_values[1] = -0x10325477;
  // Initialize the third hash value (C) with the first 32 bits of the fractional part of the square root of 5
  hash_values[2] = -0x67452302;
  // Initialize the fourth hash value (D) with the first 32 bits of the fractional part of the square root of 7
  hash_values[3] = 0x10325476;
  // Initialize the fifth hash value (E) with the first 32 bits of the fractional part of the square root of 11
  hash_values[4] = -0x3c2d1e10;
  // Return success status
  return 0;
}