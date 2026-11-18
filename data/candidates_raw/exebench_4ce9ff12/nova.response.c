static int func0(SSL *s, SSL_SESSION *ss,
                                      const unsigned char *in,
                                      size_t len, void *arg)
{
    if (arg!= NULL)
        *(size_t *)arg = len;
    return 1;
}