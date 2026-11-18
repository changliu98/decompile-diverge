int key_verify(pam_handle_t *pamh, int flags, PKCS11_KEY *key)
{
	unsigned char challenge[30];
	unsigned char signature[256];
	unsigned int siglen = sizeof(signature);
	int ok = 0;
	EVP_MD_CTX *ctx = NULL;
	EVP_PKEY *privkey = NULL;
	EVP_PKEY *pubkey = NULL;
	const EVP_MD *digest = EVP_sha1();

	ctx = EVP_MD_CTX_new();
	privkey = PKCS11_get_private_key(key);
	pubkey = PKCS11_get_public_key(key);

	if (randomize(pamh, challenge, sizeof(challenge)) != 1)
		goto out;

	if (!ctx || !privkey || !pubkey || !digest)
		goto out;

	if (!EVP_SignInit(ctx, digest) ||
	    !EVP_SignUpdate(ctx, challenge, sizeof(challenge)) ||
	    !EVP_SignFinal(ctx, signature, &siglen, privkey))
		goto out;

	if (!EVP_MD_CTX_reset(ctx) ||
	    !EVP_VerifyInit(ctx, digest) ||
	    !EVP_VerifyUpdate(ctx, challenge, sizeof(challenge)) ||
	    (EVP_VerifyFinal(ctx, signature, siglen, pubkey) != 1))
		goto out;

	ok = 1;

out:
	if (!ok) {
		pam_syslog(pamh, 7, "Error verifying key: %s\n",
			   ERR_reason_error_string(ERR_get_error()));
		prompt(flags, pamh, 3, NULL, "Error verifying key");
	}

	if (pubkey)
		EVP_PKEY_free(pubkey);
	if (privkey)
		EVP_PKEY_free(privkey);
	if (ctx)
		EVP_MD_CTX_free(ctx);

	return ok;
}