static int key_verify(pam_handle_t *pamh, int flags, char *authkey) {
 unsigned char challenge[30];
 unsigned char signature[256];
 int ok = 0;
 size_t siglen = sizeof(signature);
 EVP_MD_CTX *ctx;
 EVP_PKEY *privkey, *pubkey;
 const EVP_MD *md;

 md = EVP_sha1();
 ctx = EVP_MD_CTX_new();

 privkey = PKCS11_get_private_key(authkey);
 pubkey = PKCS11_get_public_key(authkey);

 if (randomize(pamh, challenge, sizeof(challenge)) != 1)
  goto err;

 if (pubkey == NULL || privkey == NULL || ctx == NULL ||
   md == NULL || EVP_SignInit(ctx, md) == 0 ||
   EVP_SignUpdate(ctx, challenge, sizeof(challenge)) == 0 ||
   EVP_SignFinal(ctx, signature, &siglen, privkey) == 0 ||
   EVP_MD_CTX_reset(ctx) == 0 ||
   EVP_VerifyInit(ctx, md) == 0 ||
   EVP_VerifyUpdate(ctx, challenge, sizeof(challenge)) == 0 ||
   EVP_VerifyFinal(ctx, signature, siglen, pubkey) != 1)
  goto err;

 ok = 1;

err:
 if (pubkey != NULL)
  EVP_PKEY_free(pubkey);
 if (privkey != NULL)
  EVP_PKEY_free(privkey);
 if (ctx != NULL)
  EVP_MD_CTX_free(ctx);

 if (!ok) {
  pam_syslog(pamh, LOG_ERR, "Error verifying key: %s\n",
   ERR_reason_error_string(ERR_get_error()));
  prompt(flags, pamh, 3, NULL, "Error verifying key");
 }

 return ok;
}