SSL * open_ssl_connection(rfbClient *client,int sockfd,rfbBool anonTLS,rfbCredential *cred)

{
  char *name;
  rfbBool rVar1;
  int iVar2;
  int iVar3;
  SSL_METHOD *meth;
  SSL_CTX *ctx;
  X509_VERIFY_PARAM *param_00;
  size_t namelen;
  SSL *ssl_00;
  uint8_t verify_crls;
  X509_VERIFY_PARAM *param;
  int finished;
  int n;
  SSL *ssl;
  SSL_CTX *ssl_ctx;
  rfbCredential *cred_local;
  rfbBool anonTLS_local;
  int sockfd_local;
  rfbClient *client_local;
  
  verify_crls = (cred->x509Credential).x509CrlVerifyMode;
  meth = SSLv23_client_method();
  ctx = SSL_CTX_new(meth);
  if (ctx == (SSL_CTX *)0x0) {
    (*rfbClientLog)("Could not create new SSL context.\n");
    return (SSL *)0x0;
  }
  param_00 = X509_VERIFY_PARAM_new();
  if (anonTLS == '\0') {
    if ((cred->x509Credential).x509CACertFile == (char *)0x0) {
      (*rfbClientLog)("Using default paths for certificate verification.\n");
      SSL_CTX_set_default_verify_paths(ctx);
    }
    else {
      iVar2 = SSL_CTX_load_verify_locations(ctx,(cred->x509Credential).x509CACertFile,(char *)0x0);
      if (iVar2 == 0) {
        (*rfbClientLog)("Failed to load CA certificate from %s.\n",
                        (cred->x509Credential).x509CACertFile);
        goto LAB_00101a66;
      }
    }
    if ((cred->x509Credential).x509CACrlFile != (char *)0x0) {
      rVar1 = load_crls_from_file((cred->x509Credential).x509CACrlFile,ctx);
      if (rVar1 == '\0') {
        (*rfbClientLog)("CRLs could not be loaded.\n");
        goto LAB_00101a66;
      }
      if (verify_crls == '\0') {
        verify_crls = '\x02';
      }
    }
    if (((cred->x509Credential).x509ClientCertFile != (char *)0x0) &&
       ((cred->x509Credential).x509ClientKeyFile != (char *)0x0)) {
      iVar2 = SSL_CTX_use_certificate_chain_file(ctx,(cred->x509Credential).x509ClientCertFile);
      if (iVar2 != 1) {
        (*rfbClientLog)("Client certificate could not be loaded.\n");
        goto LAB_00101a66;
      }
      iVar2 = SSL_CTX_use_PrivateKey_file(ctx,(cred->x509Credential).x509ClientKeyFile,1);
      if (iVar2 != 1) {
        (*rfbClientLog)("Client private key could not be loaded.\n");
        goto LAB_00101a66;
      }
      iVar2 = SSL_CTX_check_private_key(ctx);
      if (iVar2 == 0) {
        (*rfbClientLog)("Client certificate and private key do not match.\n");
        goto LAB_00101a66;
      }
    }
    SSL_CTX_set_verify(ctx,1,(_func_int_int_X509_STORE_CTX_ptr *)0x0);
    if (verify_crls == '\x01') {
      X509_VERIFY_PARAM_set_flags(param_00,4);
    }
    else if (verify_crls == '\x02') {
      X509_VERIFY_PARAM_set_flags(param_00,0x8004);
    }
    name = client->serverHost;
    namelen = strlen(client->serverHost);
    iVar2 = X509_VERIFY_PARAM_set1_host(param_00,name,namelen);
    if (iVar2 == 0) {
      (*rfbClientLog)("Could not set server name for verification.\n");
      goto LAB_00101a66;
    }
    SSL_CTX_set1_param(ctx,param_00);
  }
  ssl_00 = SSL_new(ctx);
  if (ssl_00 == (SSL *)0x0) {
    (*rfbClientLog)("Could not create a new SSL session.\n");
  }
  else {
    SSL_set_cipher_list(ssl_00,"ALL");
    SSL_set_fd(ssl_00,sockfd);
    SSL_CTX_set_app_data(ctx,client);
    while ((iVar2 = SSL_connect(ssl_00), iVar2 == 1 ||
           (iVar3 = wait_for_data(ssl_00,iVar2,1), iVar3 == 1))) {
      if (iVar2 == 1) {
        X509_VERIFY_PARAM_free(param_00);
        return ssl_00;
      }
    }
    SSL_shutdown(ssl_00);
    SSL_free(ssl_00);
  }
LAB_00101a66:
  X509_VERIFY_PARAM_free(param_00);
  SSL_CTX_free(ctx);
  return (SSL *)0x0;
}