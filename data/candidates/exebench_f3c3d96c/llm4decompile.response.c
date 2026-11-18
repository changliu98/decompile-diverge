void nist_increment_block(NIST_HASH_CTX *ctx)
{
    int i;
    uint32_t tmp;

    for (i = 3; i >= 0; i--) {
        tmp = ntohl(ctx->counter[i]);
        tmp++;
        ctx->counter[i] = htonl(tmp);
        if (tmp != 0)
            break;
    }
}