int key_verify(pam_handle_t *pamh,int flags,PKCS11_KEY *authkey)

{
  int iVar1;
  EVP_MD *type;
  EVP_MD_CTX *ctx;
  EVP_PKEY *pkey;
  EVP_PKEY *pkey_00;
  unsigned_long e;
  char *pcVar2;
  EVP_PKEY *pubkey;
  EVP_PKEY *privkey;
  EVP_MD_CTX *md_ctx;
  EVP_MD *md;
  uint siglen;
  uchar signature [256];
  uchar challenge [30];
  int ok;
  PKCS11_KEY *authkey_local;
  int flags_local;
  pam_handle_t *pamh_local;
  
  ok = 0;
  siglen = 0x100;
  type = EVP_sha1();
  ctx = EVP_MD_CTX_new();
  pkey = PKCS11_get_private_key(authkey);
  pkey_00 = PKCS11_get_public_key(authkey);
  iVar1 = randomize(pamh,challenge,0x1e);
  if (iVar1 == 1) {
    if ((((((pkey_00 == (EVP_PKEY *)0x0) || (pkey == (EVP_PKEY *)0x0)) || (ctx == (EVP_MD_CTX *)0x0)
          ) || ((type == (EVP_MD *)0x0 || (iVar1 = EVP_SignInit(ctx,type), iVar1 == 0)))) ||
        ((iVar1 = EVP_SignUpdate(ctx,challenge,0x1e), iVar1 == 0 ||
         ((iVar1 = EVP_SignFinal(ctx,signature,&siglen,pkey), iVar1 == 0 ||
          (iVar1 = EVP_MD_CTX_reset(ctx), iVar1 == 0)))))) ||
       ((iVar1 = EVP_VerifyInit(ctx,type), iVar1 == 0 ||
        ((iVar1 = EVP_VerifyUpdate(ctx,challenge,0x1e), iVar1 == 0 ||
         (iVar1 = EVP_VerifyFinal(ctx,signature,siglen,pkey_00), iVar1 != 1)))))) {
      e = ERR_get_error();
      pcVar2 = ERR_reason_error_string(e);
      pam_syslog(pamh,7,"Error verifying key: %s\n",pcVar2);
      prompt(flags,pamh,3,(char **)0x0,"Error verifying key");
    }
    else {
      ok = 1;
    }
  }
  if (pkey_00 != (EVP_PKEY *)0x0) {
    EVP_PKEY_free(pkey_00);
  }
  if (pkey != (EVP_PKEY *)0x0) {
    EVP_PKEY_free(pkey);
  }
  if (ctx != (EVP_MD_CTX *)0x0) {
    EVP_MD_CTX_free(ctx);
  }
  return ok;
}