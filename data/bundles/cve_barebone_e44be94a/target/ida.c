int __cdecl key_verify(pam_handle_t *pamh, int flags, PKCS11_KEY *authkey)
{
  unsigned __int64 error; // rax
  const char *v4; // rax
  pam_handle_t *v6; // [rsp+0h] [rbp-170h]
  EVP_PKEY *pubkey; // [rsp+8h] [rbp-168h]
  EVP_PKEY *privkey; // [rsp+10h] [rbp-160h]
  EVP_MD_CTX *md_ctx; // [rsp+18h] [rbp-158h]
  const EVP_MD *md; // [rsp+20h] [rbp-150h]
  unsigned int siglen; // [rsp+2Ch] [rbp-144h] BYREF
  unsigned __int8 signature[256]; // [rsp+30h] [rbp-140h] BYREF
  unsigned __int8 challenge[30]; // [rsp+130h] [rbp-40h] BYREF
  int ok; // [rsp+154h] [rbp-1Ch]
  PKCS11_KEY *authkeya; // [rsp+158h] [rbp-18h]
  int flagsa; // [rsp+164h] [rbp-Ch]
  pam_handle_t *pamha; // [rsp+168h] [rbp-8h]

  pamha = pamh;
  flagsa = flags;
  authkeya = authkey;
  ok = 0;
  siglen = 256;
  md = EVP_sha1();
  md_ctx = EVP_MD_CTX_new();
  privkey = PKCS11_get_private_key(authkeya);
  pubkey = PKCS11_get_public_key(authkeya);
  if ( randomize(pamh, challenge, 0x1Eu) == 1 )
  {
    if ( pubkey
      && privkey
      && md_ctx
      && md
      && EVP_SignInit(md_ctx, md)
      && EVP_SignUpdate(md_ctx, challenge, 0x1EuLL)
      && EVP_SignFinal(md_ctx, signature, &siglen, privkey)
      && EVP_MD_CTX_reset(md_ctx)
      && EVP_VerifyInit(md_ctx, md)
      && EVP_VerifyUpdate(md_ctx, challenge, 0x1EuLL)
      && EVP_VerifyFinal(md_ctx, signature, siglen, pubkey) == 1 )
    {
      ok = 1;
    }
    else
    {
      v6 = pamha;
      error = ERR_get_error();
      v4 = ERR_reason_error_string(error);
      pam_syslog(v6, 7, "Error verifying key: %s\n", v4);
      prompt(flagsa, pamha, 3, 0LL, "Error verifying key");
    }
  }
  if ( pubkey )
    EVP_PKEY_free(pubkey);
  if ( privkey )
    EVP_PKEY_free(privkey);
  if ( md_ctx )
    EVP_MD_CTX_free(md_ctx);
  return ok;
}