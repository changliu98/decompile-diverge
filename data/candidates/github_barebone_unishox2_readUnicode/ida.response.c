int32_t __cdecl readUnicode(const char *in, int *bit_no_p, int len)
{
  int Bit; // [rsp+4h] [rbp-2Ch]
  int count; // [rsp+8h] [rbp-28h]
  int idx; // [rsp+10h] [rbp-20h]

  idx = getStepCodeIdx(in, len, bit_no_p, 5);
  if ( idx == 99 )
    return 2147483491;
  if ( idx == 5 )
    return getStepCodeIdx(in, len, bit_no_p, 4) + 2147483392;
  if ( idx < 0 )
    return 0;
  if ( *bit_no_p >= len )
    Bit = 0;
  else
    Bit = readBit(in, *bit_no_p);
  ++*bit_no_p;
  if ( uni_bit_len[idx] + *bit_no_p - 1 >= len )
    return 2147483491;
  count = getNumFromBits(in, len, *bit_no_p, uni_bit_len[idx]) + uni_adder[idx];
  *bit_no_p += uni_bit_len[idx];
  if ( Bit )
    return -count;
  else
    return count;
}