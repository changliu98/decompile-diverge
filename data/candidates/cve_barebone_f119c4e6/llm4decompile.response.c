int
_dns_encode_HTTPS(dns_context *ctx, dns_rrs *rrs)
{
    int ret;
    char domain[256];
    char target[256];
    unsigned short *len_ptr;
    unsigned char *rr_start;
    unsigned char *start;
    int ttl;
    unsigned short priority;
    dns_https_param *param;

    memset(target, 0, 256);
    len_ptr = NULL;
    start = NULL;
    rr_start = NULL;
    ttl = 0;
    priority = 0;

    param = dns_get_HTTPS_svcparm_start(rrs, domain, 256, &ttl, &priority, target, 256);
    if (param == NULL)
    {
        tlog_ext(4, "/work/harness.c", 694, "_dns_encode_HTTPS", 0, "get https param failed.");
        return -1;
    }

    ret = _dns_encode_rr_head(ctx, domain, 0, 0, ttl, 0, &len_ptr);
    if (ret < 0)
    {
        return -1;
    }

    rr_start = ctx->ptr;

    if (_dns_left_len(ctx) < 2)
    {
        tlog_ext(4, "/work/harness.c", 705, "_dns_encode_HTTPS", 0, "left len is invalid.");
        return -1;
    }

    _dns_write_short(&ctx->ptr, priority);

    ret = _dns_encode_domain(ctx, target);
    if (ret < 0)
    {
        return -1;
    }

    start = ctx->ptr;

    while (param != NULL)
    {
        if (ctx->ptr - start > rrs->len || _dns_left_len(ctx) < 1)
        {
            return -1;
        }

        _dns_write_short(&ctx->ptr, param->key);
        _dns_write_short(&ctx->ptr, param->len);

        if (param->key <= 6)
        {
            memcpy(ctx->ptr, param + 1, param->len);
            ctx->ptr += param->len;
        }
        else
        {
            ctx->ptr -= sizeof(dns_https_param);
        }

        param = dns_get_HTTPS_svcparm_next(rrs, param);
    }

    _dns_write_short(len_ptr, (unsigned short)(ctx->ptr - rr_start));

    return 0;
}