SSL *__cdecl open_ssl_connection(rfbClient *client, int sockfd, rfbBool anonTLS, rfbCredential *cred)
{
  SSL_METHOD *v4; // rax
  size_t v5; // rax
  const char *name; // [rsp+10h] [rbp-50h]
  uint8_t verify_crls; // [rsp+1Fh] [rbp-41h]
  X509_VERIFY_PARAM *param; // [rsp+20h] [rbp-40h]
  int n; // [rsp+2Ch] [rbp-34h]
  SSL *ssl; // [rsp+30h] [rbp-30h]
  SSL_CTX *ssl_ctx; // [rsp+38h] [rbp-28h]

  verify_crls = cred->x509Credential.x509CrlVerifyMode;
  v4 = SSLv23_client_method();
  ssl_ctx = SSL_CTX_new(v4);
  if ( !ssl_ctx )
  {
    rfbClientLog("Could not create new SSL context.\n");
    return 0LL;
  }
  param = X509_VERIFY_PARAM_new();
  if ( !anonTLS )
  {
    if ( cred->x509Credential.x509CACertFile )
    {
      if ( !SSL_CTX_load_verify_locations(ssl_ctx, cred->x509Credential.x509CACertFile, 0LL) )
      {
        rfbClientLog("Failed to load CA certificate from %s.\n", cred->x509Credential.x509CACertFile);
error_free_ctx:
        X509_VERIFY_PARAM_free(param);
        SSL_CTX_free(ssl_ctx);
        return 0LL;
      }
    }
    else
    {
      rfbClientLog("Using default paths for certificate verification.\n");
      SSL_CTX_set_default_verify_paths(ssl_ctx);
    }
    if ( cred->x509Credential.x509CACrlFile )
    {
      if ( !load_crls_from_file(cred->x509Credential.x509CACrlFile, ssl_ctx) )
      {
        rfbClientLog("CRLs could not be loaded.\n");
        goto error_free_ctx;
      }
      if ( !verify_crls )
        verify_crls = 2;
    }
    if ( cred->x509Credential.x509ClientCertFile && cred->x509Credential.x509ClientKeyFile )
    {
      if ( SSL_CTX_use_certificate_chain_file(ssl_ctx, cred->x509Credential.x509ClientCertFile) != 1 )
      {
        rfbClientLog("Client certificate could not be loaded.\n");
        goto error_free_ctx;
      }
      if ( SSL_CTX_use_PrivateKey_file(ssl_ctx, cred->x509Credential.x509ClientKeyFile, 1) != 1 )
      {
        rfbClientLog("Client private key could not be loaded.\n");
        goto error_free_ctx;
      }
      if ( !SSL_CTX_check_private_key(ssl_ctx) )
      {
        rfbClientLog("Client certificate and private key do not match.\n");
        goto error_free_ctx;
      }
    }
    SSL_CTX_set_verify(ssl_ctx, 1, 0LL);
    if ( verify_crls == 1 )
    {
      X509_VERIFY_PARAM_set_flags(param, 4uLL);
    }
    else if ( verify_crls == 2 )
    {
      X509_VERIFY_PARAM_set_flags(param, 0x8004uLL);
    }
    name = client->serverHost;
    v5 = strlen(client->serverHost);
    if ( !X509_VERIFY_PARAM_set1_host(param, name, v5) )
    {
      rfbClientLog("Could not set server name for verification.\n");
      goto error_free_ctx;
    }
    SSL_CTX_set1_param(ssl_ctx, param);
  }
  ssl = SSL_new(ssl_ctx);
  if ( !ssl )
  {
    rfbClientLog("Could not create a new SSL session.\n");
    goto error_free_ctx;
  }
  SSL_set_cipher_list(ssl, "ALL");
  SSL_set_fd(ssl, sockfd);
  SSL_CTX_set_app_data(ssl_ctx, client);
  do
  {
    n = SSL_connect(ssl);
    if ( n != 1 && wait_for_data(ssl, n, 1) != 1 )
    {
      SSL_shutdown(ssl);
      SSL_free(ssl);
      goto error_free_ctx;
    }
  }
  while ( n != 1 );
  X509_VERIFY_PARAM_free(param);
  return ssl;
}