SSL *open_ssl_connection(rfbClient *client, int sockfd, rfbBool anonTLS,
                                rfbCredential *cred)
{
    SSL_CTX *ssl_ctx;
    SSL *ssl;
    int rv;
    unsigned char crl_verify_mode = cred->x509Credential.x509CrlVerifyMode;
    X509_VERIFY_PARAM *param;

    ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    if (ssl_ctx == NULL) {
        rfbClientLog.Error("Could not create new SSL context.\n");
        return NULL;
    }

    param = X509_VERIFY_PARAM_new();

    if (!anonTLS) {
        if (cred->x509Credential.x509CACertFile) {
            rv = SSL_CTX_load_verify_locations(ssl_ctx,
                                               cred->x509Credential.x509CACertFile,
                                               NULL);
            if (rv == 0) {
                rfbClientLog.Error("Failed to load CA certificate from %s.\n",
                                   cred->x509Credential.x509CACertFile);
                goto out;
            }
        } else {
            rfbClientLog.Info("Using default paths for certificate verification.\n");
            SSL_CTX_set_default_verify_paths(ssl_ctx);
        }

        if (cred->x509Credential.x509CACrlFile) {
            if (!load_crls_from_file(cred->x509Credential.x509CACrlFile, ssl_ctx)) {
                rfbClientLog.Error("CRLs could not be loaded.\n");
                goto out;
            }
            if (crl_verify_mode == 0) {
                crl_verify_mode = 2;
            }
        }

        if (cred->x509Credential.x509ClientCertFile &&
            cred->x509Credential.x509ClientKeyFile) {
            rv = SSL_CTX_use_certificate_chain_file(ssl_ctx,
                                                    cred->x509Credential.x509ClientCertFile);
            if (rv != 1) {
                rfbClientLog.Error("Client certificate could not be loaded.\n");
                goto out;
            }
            rv = SSL_CTX_use_PrivateKey_file(ssl_ctx,
                                             cred->x509Credential.x509ClientKeyFile,
                                             1);
            if (rv != 1) {
                rfbClientLog.Error("Client private key could not be loaded.\n");
                goto out;
            }
            rv = SSL_CTX_check_private_key(ssl_ctx);
            if (rv == 0) {
                rfbClientLog.Error("Client certificate and private key do not match.\n");
                goto out;
            }
        }

        SSL_CTX_set_verify(ssl_ctx, 1, NULL);

        if (crl_verify_mode == 1) {
            X509_VERIFY_PARAM_set_flags(param, 0x00000004);
        } else if (crl_verify_mode == 2) {
            X509_VERIFY_PARAM_set_flags(param, 0x00008000 | 0x00000004);
        }

        rv = X509_VERIFY_PARAM_set1_host(param,
                                         client->serverHost,
                                         strlen(client->serverHost));
        if (rv == 0) {
            rfbClientLog.Error("Could not set server name for verification.\n");
            goto out;
        }

        SSL_CTX_set1_param(ssl_ctx, param);
    }

    ssl = SSL_new(ssl_ctx);
    if (ssl == NULL) {
        rfbClientLog.Error("Could not create a new SSL session.\n");
        goto out;
    }

    SSL_set_cipher_list(ssl, "ALL");
    SSL_set_fd(ssl, sockfd);
    SSL_CTX_set_app_data(ssl_ctx, client);

    while (1) {
        rv = SSL_connect(ssl);
        if (rv == 1) {
            break;
        }
        rv = wait_for_data(ssl, rv, 1);
        if (rv != 1) {
            SSL_shutdown(ssl);
            SSL_free(ssl);
            goto out;
        }
    }

    X509_VERIFY_PARAM_free(param);

    return ssl;

out:
    X509_VERIFY_PARAM_free(param);
    SSL_CTX_free(ssl_ctx);
    return NULL;
}