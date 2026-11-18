// Calculates the next hash index in a circular hash table.
// Takes the previous hash index, increments it by 1, and applies a bitmask
// to wrap around to the valid range [0, HASHTABLE_NSLOT - 1].
int walNextHash(int previous_hash_index)
{
  // Increment by 1 and mask with HASHTABLE_NSLOT - 1 to ensure the result
  // stays within the bounds of the hash table size (assumes HASHTABLE_NSLOT is a power of 2).
  return previous_hash_index + 1U & HASHTABLE_NSLOT - 1U;
}