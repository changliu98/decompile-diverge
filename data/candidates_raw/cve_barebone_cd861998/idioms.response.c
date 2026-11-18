struct rfbSSL *open_ssl_connection(struct rfbClient *client, int sockfd, _Bool anonTLS, struct rfbCredential *cred)
{
    struct rfbSSL *ssl;
    struct SSL_CTX *ctx;
    struct X509_VERIFY_PARAM *param;
    int ret;
    int verify_crls = cred->x509Credential.x509CrlVerifyMode;
    if ((ctx = SSL_CTX_new(SSLv23_client_method())) == ((void *)0))
    {
        rfbClientLog("Could not create new SSL context.\n");
        return ((void *)0);
    }
    param = X509_VERIFY_PARAM_new();
    if (!anonTLS)
    {
        if (cred->x509Credential.x509CACertFile == ((void *)0))
        {
            rfbClientLog("Using default paths for certificate verification.\n");
            SSL_CTX_set_default_verify_paths(ctx);
        }
        else if (SSL_CTX_load_verify_locations(ctx,
            cred->x509Credential.x509CACertFile, ((void *)0)) == 0)
        {
            rfbClientLog("Failed to load CA certificate from %s.\n",
                cred->x509Credential.x509CACertFile);
            goto error_free_ctx;
        }
        if (cred->x509Credential.x509CACrlFile != ((void *)0))
        {
            if (load_crls_from_file(cred->x509Credential.x509CACrlFile, ctx)
                == ((void *)0))
            {
                rfbClientLog("CRLs could not be loaded.\n");
                goto error_free_ctx;
            }
            if (verify_crls == 0)
                verify_crls = 2;
        }
        if (cred->x509Credential.x509ClientCertFile != ((void *)0) &&
            cred->x509Credential.x509ClientKeyFile != ((void *)0))
        {
            if (SSL_CTX_use_certificate_chain_file(ctx,
                cred->x509Credential.x509ClientCertFile) != 1)
            {
                rfbClientLog("Client certificate could not be loaded.\n");
                goto error_free_ctx;
            }
            if (SSL_CTX_use_PrivateKey_file(ctx,
                cred->x509Credential.x509ClientKeyFile,
                SSL_FILETYPE_PEM) != 1)
            {
                rfbClientLog("Client private key could not be loaded.\n");
                goto error_free_ctx;
            }
            if (SSL_CTX_check_private_key(ctx) == 0)
            {
                rfbClientLog("Client certificate and private key do not "
                    "match.\n");
                goto error_free_ctx;
            }
        }
        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, ((void *)0));
        if (verify_crls == 1)
            X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_CRL_CHECK);
        else if (verify_crls == 2)
            X509_VERIFY_PARAM_set_flags(param,
                X509_V_FLAG_CRL_CHECK | X509_V_FLAG_CRL_CHECK_ALL);
        if (X509_VERIFY_PARAM_set1_host(param, client->serverHost,
            strlen(client->serverHost)) == 0)
        {
            rfbClientLog("Could not set server name for verification.\n");
            goto error_free_ctx;
        }
        SSL_CTX_set1_param(ctx, param);
    }
    if ((ssl = SSL_new(ctx)) == ((void *)0))
    {
        rfbClientLog("Could not create a new SSL session.\n");
        goto error_free_ctx;
    }
    SSL_set_cipher_list(ssl, "ALL");
    SSL_set_fd(ssl, sockfd);
    SSL_CTX_set_app_data(ctx, client);
    do
    {
        ret = SSL_connect(ssl);
        if (ret != 1 && wait_for_data(ssl, ret, 1) != 1)
        {
            SSL_shutdown(ssl);
            SSL_free(ssl);
            goto error_free_ctx;
        }
    } while (ret != 1);
    X509_VERIFY_PARAM_free(param);
    return (struct rfbSSL *)ssl;
error_free_ctx:
    X509_VERIFY_PARAM_free(param);
    SSL_CTX_free(ctx);
    return ((void *)0);
}