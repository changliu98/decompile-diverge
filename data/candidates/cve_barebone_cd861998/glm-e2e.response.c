SSL* open_ssl_connection(rfbClient *client, int sockfd, unsigned char anonTLS, rfbCredential *cred) {
    SSL *ssl = NULL;
    SSL_CTX *ctx = NULL;
    int ret = 0;
    int err = 0;
    X509_VERIFY_PARAM *param;
    unsigned char pm;

    pm = cred->x509KeyPM;

    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) {
        rfbClientLog("SSL_CTX_new failed\n");
        return NULL;
    }

    param = X509_VERIFY_PARAM_new();

    if (!anonTLS) {
        if (cred->x509CACertFile != NULL) {
            if (SSL_CTX_load_verify_locations(ctx, cred->x509CACertFile, NULL) == 0) {
                rfbClientLog("Failed to load CA cert: %s\n", cred->x509CACertFile);
                goto fail;
            }
        } else {
            rfbClientLog("Using default system CA cert\n");
            SSL_CTX_set_default_verify_paths(ctx);
        }

        if (cred->x509CRLFile != NULL) {
            if (load_crls_from_file(cred->x509CRLFile, ctx) == 0) {
                rfbClientLog("Failed to load CRL: %s\n", cred->x509CRLFile);
                goto fail;
            }
            if (pm == 0) {
                pm = 2;
            }
        }

        if (cred->x509ClientCertFile != NULL && cred->x509ClientKeyFile != NULL) {
            if (SSL_CTX_use_certificate_chain_file(ctx, cred->x509ClientCertFile) != 1) {
                rfbClientLog("Failed to load client cert: %s\n", cred->x509ClientCertFile);
                goto fail;
            }
            if (SSL_CTX_use_PrivateKey_file(ctx, cred->x509ClientKeyFile, 1) != 1) {
                rfbClientLog("Failed to load client key: %s\n", cred->x509ClientKeyFile);
                goto fail;
            }
            if (SSL_CTX_check_private_key(ctx) == 0) {
                rfbClientLog("Client cert and key do not match\n");
                goto fail;
            }
        }

        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

        if (pm == 1) {
            X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_CRL_CHECK);
        } else if (pm == 2) {
            X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_CRL_CHECK | X509_V_FLAG_CRL_CHECK_ALL);
        }

        if (X509_VERIFY_PARAM_set1_host(param, client->host, strlen(client->host)) == 0) {
            rfbClientLog("Failed to set hostname for verification\n");
            goto fail;
        }
        SSL_CTX_set1_param(ctx, param);
    }

    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        rfbClientLog("SSL_new failed\n");
        goto fail;
    }

    SSL_set_cipher_list(ssl, "ALL:!COMPLEMENTOFDEFAULT:!eNULL");
    SSL_set_fd(ssl, sockfd);
    SSL_CTX_set_app_data(ctx, client);

    do {
        ret = SSL_connect(ssl);
        if (ret != 1) {
            if (wait_for_data(ssl, ret, 1) != 1) {
                err = 1;
                SSL_shutdown(ssl);
                break;
            }
        }
    } while (ret != 1 && err != 1);

    if (err != 1) {
        X509_VERIFY_PARAM_free(param);
        return ssl;
    }

    SSL_free(ssl);

fail:
    X509_VERIFY_PARAM_free(param);
    SSL_CTX_free(ctx);
    return NULL;
}