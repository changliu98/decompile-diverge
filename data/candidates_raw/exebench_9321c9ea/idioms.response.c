int sha256_get_digest_size(unsigned int *ret_digest_len)
{
  *ret_digest_len = SHA256_DIGEST_SIZE;
  return 0;
}