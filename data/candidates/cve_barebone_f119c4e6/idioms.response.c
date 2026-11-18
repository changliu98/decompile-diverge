int _dns_encode_HTTPS(struct _dns_context *context, struct _dns_rrs *rrs)
{
  struct _dns_context *ctx = context;
  struct _dns_rrs *rr = rrs;
  int ret = 0;
  int qtype = DNS_TYPE_HTTPS;
  int qclass = DNS_CLASS_IN;
  char name[256] = { 0 };
  char *len = ((void *)0);
  char *start = ((void *)0);
  char *rrstart = ((void *)0);
  int ttl = 0;
  int priority = 0;
  struct _dns_https_param *param = ((void *)0);
  param = get_https_param(rr, name, sizeof(name), &ttl, &priority, name, sizeof(name));
  if (param == ((void *)0))
  {
    do { _dns_log(4, "/work/harness.c", 694, __FUNCTION__, ((void *)0), "get https param failed."); } while (0);
    return -1;
  }
  ret = dns_encode_rr_head(ctx, name, qtype, qclass, ttl, 0, &len);
  if (ret < 0)
  {
    return -1;
  }
  rrstart = ctx->ptr;
  if (dns_left_len(ctx) < 2)
  {
    do { _dns_log(4, "/work/harness.c", 705, __FUNCTION__, ((void *)0), "left len is invalid."); } while (0);
    return -1;
  }
  dns_write_short(&ctx->ptr, priority);
  ret = dns_encode_domain(ctx, name);
  if (ret < 0)
  {
    return -1;
  }
  start = ctx->ptr;
  while (param != ((void *)0))
  {
    if (ctx->ptr - start > rr->len || dns_left_len(ctx) <= 0)
    {
      return -1;
    }
    dns_write_short(&ctx->ptr, param->key);
    dns_write_short(&ctx->ptr, param->len);
    if (param->key < DNS_HTTPS_KEY_END)
    {
      memcpy(ctx->ptr, param->value, param->len);
      ctx->ptr += param->len;
    }
    else
    {
      ctx->ptr -= 4;
    }
    param = get_next_param(rr, param);
  }
  dns_write_short(&len, (ctx->ptr - rrstart));
  return 0;
}