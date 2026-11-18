int __cdecl dns_encode_HTTPS(dns_context *context, dns_rrs *rrs)
{
  dns_https_param *param;
  int priority;
  int ttl;
  unsigned __int8 *rr_start;
  unsigned __int8 *start;
  unsigned __int8 *rr_len_ptr;
  char target[256];
  char domain[256];
  int ret;

  rr_len_ptr = NULL;
  start = NULL;
  rr_start = NULL;
  ttl = 0;
  priority = 0;
  memset(target, 0, sizeof(target));

  param = dns_get_HTTPS_svcparm_start(rrs, domain, 256, &ttl, &priority, target, 256);
  if (!param)
  {
    tlog_ext(4, "/work/harness.c", 694, "_dns_encode_HTTPS", 0LL, "get https param failed.");
    return -1;
  }

  // qtype and qclass are uninitialized in the original binary, passing 0
  ret = dns_encode_rr_head(context, domain, 0, 0, ttl, 0, &rr_len_ptr);
  if (ret < 0)
  {
    return -1;
  }

  rr_start = context->ptr;
  if (dns_left_len(context) < 2)
  {
    tlog_ext(4, "/work/harness.c", 705, "_dns_encode_HTTPS", 0LL, "left len is invalid.");
    return -1;
  }

  dns_write_short(&context->ptr, priority);
  ret = dns_encode_domain(context, target);
  if (ret < 0)
  {
    return -1;
  }

  start = context->ptr;
  while (param)
  {
    if (context->ptr - start > rrs->len || dns_left_len(context) <= 0)
    {
      return -1;
    }

    dns_write_short(&context->ptr, param->key);
    dns_write_short(&context->ptr, param->len);

    if (param->key > 6u)
    {
      // Undo the 4-byte write of key and len if key is out of expected bounds
      context->ptr -= 4;
    }
    else
    {
      memcpy(context->ptr, param->value, param->len);
      context->ptr += param->len;
    }

    param = dns_get_HTTPS_svcparm_next(rrs, param);
  }

  dns_write_short(&rr_len_ptr, (unsigned __int16)(context->ptr - rr_start));
  return 0;
}