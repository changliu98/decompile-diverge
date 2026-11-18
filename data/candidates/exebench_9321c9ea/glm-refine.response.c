int __cdecl sha256_init_hash(unsigned int *ret_digest_len)
{
  if (ret_digest_len) {
      *ret_digest_len = 32; // 32 bytes = 256 bits
  }
  return 0; // STATUS_SUCCESS
}