int sha256_init_hash(unsigned int *ret_digest_len)
{
  *ret_digest_len = SHA256_DIGEST_SIZE;
  return 0;
}