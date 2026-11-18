SSL *open_ssl_connection(rfbClientOnlyClient *cl, int sock, rfbBool noverify,
                         rfbClientOnlyOptions *opts) {
  SSL *ssl;
  SSL_CTX *ctx;
  X509_VERIFY_PARAM *param;
  int ret;
  int verify_mode = opts->verify_mode;
  ctx = SSL_CTX_new(SSLv23_client_method());
  if (!ctx) {
    rfbClientLog("Could not create new SSL context.\n");
    return NULL;
  }
  param = X509_VERIFY_PARAM_new();
  if (!noverify) {
    if (opts->ca_file) {
      if (SSL_CTX_load_verify_locations(ctx, opts->ca_file, NULL) == 0) {
        rfbClientLog("Failed to load CA certificate from %s.\n",
                     opts->ca_file);
        goto error_free_ctx;
      }
    } else {
      rfbClientLog("Using default paths for certificate verification.\n");
      SSL_CTX_set_default_verify_paths(ctx);
    }
    if (opts->crl_file) {
      if (load_crls_from_file(opts->crl_file, ctx) == 0) {
        rfbClientLog("CRLs could not be loaded.\n");
        goto error_free_ctx;
      }
      if (verify_mode == 0) verify_mode = 2;
    }
    if (opts->cert_file && opts->key_file) {
      if (SSL_CTX_use_certificate_chain_file(ctx, opts->cert_file) != 1) {
        rfbClientLog("Client certificate could not be loaded.\n");
        goto error_free_ctx;
      }
      if (SSL_CTX_use_PrivateKey_file(ctx, opts->key_file, 1) != 1) {
        rfbClientLog("Client private key could not be loaded.\n");
        goto error_free_ctx;
      }
      if (SSL_CTX_check_private_key(ctx) == 0) {
        rfbClientLog("Client certificate and private key do not match.\n");
        goto error_free_ctx;
      }
    }
    SSL_CTX_set_verify(ctx, 1, NULL);
    if (verify_mode == 1)
      X509_VERIFY_PARAM_set_flags(param, 0x00000004);
    else if (verify_mode == 2)
      X509_VERIFY_PARAM_set_flags(param, 0x00008004);
    if (X509_VERIFY_PARAM_set1_host(param, cl->host, strlen(cl->host)) ==
        NULL) {
      rfbClientLog("Could not set server name for verification.\n");
      goto error_free_ctx;
    }
    SSL_CTX_set1_param(ctx, param);
  }
  ssl = SSL_new(ctx);
  if (!ssl) {
    rfbClientLog("Could not create a new SSL session.\n");
    goto error_free_ctx;
  }
  SSL_set_cipher_list(ssl, "ALL");
  SSL_set_fd(ssl, sock);
  SSL_CTX_set_app_data(ctx, cl);
  do {
    ret = SSL_connect(ssl);
    if (ret != 1) {
      if (wait_for_data(ssl, ret, 1) != 1) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        goto error_free_ctx;
      }
    }
  } while (ret != 1);
  X509_VERIFY_PARAM_free(param);
  return ssl;
error_free_ctx:
  X509_VERIFY_PARAM_free(param);
  SSL_CTX_free(ctx);
  return NULL;
}