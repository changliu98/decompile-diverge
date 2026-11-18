int __cdecl func0(int n)
{
  int res = 0;
  int bit_length = 0;

  // Calculate the bit-length of 'n' (number of bits required to represent n)
  for (int temp = n; temp > 0; temp >>= 1)
    bit_length++;

  // Create a mask where all even-indexed bits up to the bit-length are set to 1.
  // (e.g., if bit_length is 5, mask becomes 0b10101)
  for (int i = 0; i < bit_length; i += 2)
    res |= (1 << i);

  // XOR the original number with the generated mask
  return res ^ n;
}