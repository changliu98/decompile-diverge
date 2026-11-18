void crypto_eddsa_sign(void *sig, void *sk, void *m, unsigned long long mlen)
{
  unsigned char a[-1];
  unsigned char r[-1];
  unsigned char s[-1];
  unsigned char *sigptr = sig;
  unsigned char *skptr = sk;
  unsigned char *mptr = m;
  unsigned long long mllen = mlen;
  crypto_blake2b(a, sizeof a, skptr, sizeof a);
  crypto_eddsa_trim_scalar(a, a);
  hash_reduce(r, a + 32, sizeof a - 32, mptr, mllen, ((void *)0), 0);
  crypto_eddsa_scalarbase(s, r);
  hash_reduce(a, s, sizeof a - 32, skptr + 32, sizeof a - 32, mptr, mllen);
  for (unsigned long long i = 0; i < sizeof s; i++)
    sigptr[i] = s[i];
  crypto_eddsa_mul_add(sigptr + sizeof s, a, a + sizeof a - sizeof s, r);
  crypto_wipe(a, sizeof a);
  crypto_wipe(r, sizeof r);
}