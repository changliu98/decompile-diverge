void __cdecl poly1305_squeeze(unsigned __int8 *h, unsigned __int64 *hr)
{
  unsigned __int64 carry;
  unsigned int i;

  // 1. Serialize the first 16 limbs (128 bits) of the hash state into bytes
  carry = 0;
  for (i = 0; i < 0x10; ++i)
  {
    carry += hr[i];
    h[i] = (unsigned __int8)carry;
    carry >>= 8;
  }

  // 2. Process the 17th limb and apply the Poly1305 partial reduction
  // The 17th byte is masked to 2 bits, and the overflow is multiplied by 5
  // (which corresponds to reducing modulo 2^130 - 5)
  carry += hr[16];
  h[16] = (unsigned __int8)carry & 3;
  carry = 5 * (carry >> 2);

  // 3. Propagate the carry from the reduction back into the first 16 bytes
  for (i = 0; i < 0x10; ++i)
  {
    carry += h[i];
    h[i] = (unsigned __int8)carry;
    carry >>= 8;
  }

  // 4. Add any remaining carry to the 17th byte
  h[16] += (unsigned __int8)carry;
}