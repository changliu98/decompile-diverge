int key_verify(pam_handle_t *pamh, int tty, PKCS11_SESSION *session) {
  int ret = 0;
  unsigned char sig[256];
  unsigned char rand[30];
  unsigned int siglen = 256;
  const EVP_MD *md = EVP_sha1();
  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  EVP_PKEY *priv = PKCS11_get_private_key(session);
  EVP_PKEY *pub = PKCS11_get_public_key(session);
  if (randomize(pamh, rand, 30) == 1) {
    if (pub != NULL && priv != NULL && ctx != NULL && md != NULL &&
        EVP_SignInit(ctx, md) && EVP_SignUpdate(ctx, rand, 30) &&
        EVP_SignFinal(ctx, sig, &siglen, priv) && EVP_MD_CTX_reset(ctx) &&
        EVP_VerifyInit(ctx, md) && EVP_VerifyUpdate(ctx, rand, 30) &&
        EVP_VerifyFinal(ctx, sig, siglen, pub) == 1) {
      ret = 1;
    } else {
      pam_syslog(pamh, 7, "Error verifying key: %s\n",
                 ERR_reason_error_string(ERR_get_error()));
      prompt(tty, pamh, 3, NULL, "Error verifying key");
    }
  }
  if (pub != NULL) EVP_PKEY_free(pub);
  if (priv != NULL) EVP_PKEY_free(priv);
  if (ctx != NULL) EVP_MD_CTX_free(ctx);
  return ret;
}