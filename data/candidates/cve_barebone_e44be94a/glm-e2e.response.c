int key_verify(pam_handle_t *pamh, int arg, void *key) {
    unsigned char buf[30];
    unsigned char sig[256];
    unsigned int sig_len = 256;
    int ret = 0;

    const EVP_MD *md = EVP_sha1();
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    EVP_PKEY *priv_key = PKCS11_get_private_key(key);
    EVP_PKEY *pub_key = PKCS11_get_public_key(key);

    if (randomize(pamh, buf, 30) != 1) {
        goto cleanup;
    }

    if (!pub_key || !priv_key || !md_ctx || !md) {
        goto error;
    }

    if (EVP_SignInit(md_ctx, md) == 0) {
        goto error;
    }

    if (EVP_SignUpdate(md_ctx, buf, 30) == 0) {
        goto error;
    }

    if (EVP_SignFinal(md_ctx, sig, &sig_len, priv_key) == 0) {
        goto error;
    }

    if (EVP_MD_CTX_reset(md_ctx) == 0) {
        goto error;
    }

    if (EVP_VerifyInit(md_ctx, md) == 0) {
        goto error;
    }

    if (EVP_VerifyUpdate(md_ctx, buf, 30) == 0) {
        goto error;
    }

    if (EVP_VerifyFinal(md_ctx, sig, sig_len, pub_key) != 1) {
        goto error;
    }

    ret = 1;
    goto cleanup;

error:
    {
        unsigned long err = ERR_get_error();
        const char *err_str = ERR_reason_error_string(err);
        pam_syslog(pamh, LOG_ERR, "%s", err_str);
        prompt(pamh, arg, 3, "%s", "Error"); // String at 0x2020 inferred as generic error prompt
    }

cleanup:
    if (pub_key) {
        EVP_PKEY_free(pub_key);
    }
    if (priv_key) {
        EVP_PKEY_free(priv_key);
    }
    if (md_ctx) {
        EVP_MD_CTX_free(md_ctx);
    }

    return ret;
}