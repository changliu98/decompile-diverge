int __cdecl key_verify(pam_handle_t *pamh, int flags, PKCS11_KEY *authkey)
{
  EVP_PKEY *pubkey = NULL;
  EVP_PKEY *privkey = NULL;
  EVP_MD_CTX *md_ctx = NULL;
  const EVP_MD *md = NULL;
  
  unsigned int siglen = 256;
  unsigned __int8 signature[256];
  unsigned __int8 challenge[30];
  
  int ok = 0;

  md = EVP_sha1();
  md_ctx = EVP_MD_CTX_new();
  privkey = PKCS11_get_private_key(authkey);
  pubkey = PKCS11_get_public_key(authkey);

  if (randomize(pamh, challenge, 30) == 1)
  {
    if (pubkey
      && privkey
      && md_ctx
      && md
      && EVP_SignInit(md_ctx, md)
      && EVP_SignUpdate(md_ctx, challenge, 30)
      && EVP_SignFinal(md_ctx, signature, &siglen, privkey)
      && EVP_MD_CTX_reset(md_ctx)
      && EVP_VerifyInit(md_ctx, md)
      && EVP_VerifyUpdate(md_ctx, challenge, 30)
      && EVP_VerifyFinal(md_ctx, signature, siglen, pubkey) == 1)
    {
      ok = 1;
    }
    else
    {
      unsigned __int64 error = ERR_get_error();
      const char *err_str = ERR_reason_error_string(error);
      pam_syslog(pamh, 7, "Error verifying key: %s\n", err_str);
      prompt(flags, pamh, 3, NULL, "Error verifying key");
    }
  }

  if (pubkey)
    EVP_PKEY_free(pubkey);
  if (privkey)
    EVP_PKEY_free(privkey);
  if (md_ctx)
    EVP_MD_CTX_free(md_ctx);

  return ok;
}