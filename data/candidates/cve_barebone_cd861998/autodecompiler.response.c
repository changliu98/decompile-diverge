static SSL* open_ssl_connection(rfbClient* client, int sock, char useSSL,
                                 struct sslStruct* ssl)
{
  SSL_CTX *ctx = NULL;
  SSL *sslconn = NULL;
  X509_VERIFY_PARAM *param;
  unsigned char verify_crls = ssl->verifyCRLs;
  int status, finished = 0;

  if (!(ctx = SSL_CTX_new(SSLv23_client_method()))) {
    rfbClientLog("Could not create new SSL context.\n");
    return NULL;
  }

  param = X509_VERIFY_PARAM_new();

  if (!useSSL) {

    if (ssl->CAfile) {
      if (!SSL_CTX_load_verify_locations(ctx, ssl->CAfile, NULL)) {
        rfbClientLog("Failed to load CA certificate from %s.\n", ssl->CAfile);
        goto error_free_ctx;
      }
    } else {
      rfbClientLog("Using default paths for certificate verification.\n");
      SSL_CTX_set_default_verify_paths(ctx);
    }


    if (ssl->crlFile) {
      if (!load_crls_from_file(ssl->crlFile, ctx)) {
        rfbClientLog("CRLs could not be loaded.\n");
        goto error_free_ctx;
      }
      if (verify_crls == 0)
        verify_crls = 2;
    }


    if (ssl->certFile && ssl->keyFile) {
      if (SSL_CTX_use_certificate_chain_file(ctx, ssl->certFile) != 1) {
        rfbClientLog("Client certificate could not be loaded.\n");
        goto error_free_ctx;
      }
      if (SSL_CTX_use_PrivateKey_file(ctx, ssl->keyFile, 1) != 1) {
        rfbClientLog("Client private key could not be loaded.\n");
        goto error_free_ctx;
      }
      if (!SSL_CTX_check_private_key(ctx)) {
        rfbClientLog("Client certificate and private key do not match.\n");
        goto error_free_ctx;
      }
    } else {
      SSL_CTX_set_verify(ctx, 1, NULL);
      if (verify_crls == 1)
        X509_VERIFY_PARAM_set_flags(param, 4);
      else if (verify_crls == 2)
        X509_VERIFY_PARAM_set_flags(param, 4 | 0x8000);
    }


    X509_VERIFY_PARAM_set1_host(param, client->hostname,
                                strlen(client->hostname));
    if (!X509_VERIFY_PARAM_set1_host(param, client->hostname,
                                      strlen(client->hostname))) {
      rfbClientLog("Could not set server name for verification.\n");
      goto error_free_ctx;
    }
    SSL_CTX_set1_param(ctx, param);
  }

  if (!(sslconn = SSL_new(ctx))) {
    rfbClientLog("Could not create a new SSL session.\n");
    goto error_free_ctx;
  }

  SSL_set_cipher_list(sslconn, "ALL");

  SSL_set_fd(sslconn, sock);
  SSL_CTX_set_app_data(ctx, client);

  do {
    status = SSL_connect(sslconn);
    if (status != 1) {
      if (wait_for_data(sslconn, status, 1) != 1) {
        finished = 1;
        SSL_shutdown(sslconn);
        goto error_free_ssl;
      }
    }
  } while (status != 1 && !finished);

  X509_VERIFY_PARAM_free(param);

  return sslconn;

error_free_ssl:
  SSL_free(sslconn);
error_free_ctx:
  X509_VERIFY_PARAM_free(param);
  SSL_CTX_free(ctx);
  return NULL;
}