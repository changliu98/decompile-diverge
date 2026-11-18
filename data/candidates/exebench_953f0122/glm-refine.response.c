int __cdecl murmur3_init_hash(unsigned int *ret_digest_len)
{
  if (ret_digest_len) {
    *ret_digest_len = 16; // 16 bytes = 128 bits (MurmurHash3 x86_128 / x64_128)
  }
  return 0; // STATUS_SUCCESS
}