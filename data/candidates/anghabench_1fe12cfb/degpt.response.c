// Calculates the next hash index by incrementing the previous hash and wrapping around using modulo arithmetic.
int walNextHash(int previous_hash)
{
  // Increment the previous hash value by 1, then apply bitwise AND with HASHTABLE_NSLOT - 1 to ensure the result stays within the valid range [0, HASHTABLE_NSLOT - 1].
  return previous_hash + 1U & HASHTABLE_NSLOT - 1U;
}