int __cdecl dns_encode_HTTPS(dns_context *context, dns_rrs *rrs)
{
  dns_https_param *param; // [rsp+8h] [rbp-258h]
  int priority; // [rsp+10h] [rbp-250h] BYREF
  int ttl; // [rsp+14h] [rbp-24Ch] BYREF
  unsigned __int8 *rr_start; // [rsp+18h] [rbp-248h]
  unsigned __int8 *start; // [rsp+20h] [rbp-240h]
  unsigned __int8 *rr_len_ptr; // [rsp+28h] [rbp-238h] BYREF
  char target[256]; // [rsp+30h] [rbp-230h] BYREF
  char domain[256]; // [rsp+130h] [rbp-130h] BYREF
  int qclass; // [rsp+23Ch] [rbp-24h]
  int qtype; // [rsp+240h] [rbp-20h]
  int ret; // [rsp+244h] [rbp-1Ch]
  dns_rrs *rrsa; // [rsp+248h] [rbp-18h]
  dns_context *contexta; // [rsp+250h] [rbp-10h]

  contexta = context;
  rrsa = rrs;
  ret = 0;
  qtype = 0;
  qclass = 0;
  memset(target, 0, sizeof(target));
  rr_len_ptr = 0LL;
  start = 0LL;
  rr_start = 0LL;
  ttl = 0;
  priority = 0;
  param = dns_get_HTTPS_svcparm_start(rrsa, domain, 256, &ttl, &priority, target, 256);
  if ( param )
  {
    ret = dns_encode_rr_head(contexta, domain, qtype, qclass, ttl, 0, &rr_len_ptr);
    if ( ret >= 0 )
    {
      rr_start = contexta->ptr;
      if ( dns_left_len(contexta) >= 2 )
      {
        dns_write_short(&contexta->ptr, priority);
        ret = dns_encode_domain(contexta, target);
        if ( ret >= 0 )
        {
          start = contexta->ptr;
          while ( param )
          {
            if ( contexta->ptr - start > rrsa->len || dns_left_len(contexta) <= 0 )
              return -1;
            dns_write_short(&contexta->ptr, param->key);
            dns_write_short(&contexta->ptr, param->len);
            if ( param->key > 6u )
            {
              contexta->ptr -= 4;
            }
            else
            {
              memcpy(contexta->ptr, param->value, param->len);
              contexta->ptr += param->len;
            }
            param = dns_get_HTTPS_svcparm_next(rrsa, param);
          }
          dns_write_short(&rr_len_ptr, (unsigned __int16)&contexta->ptr[-(_WORD)rr_start]);
          return 0;
        }
        else
        {
          return -1;
        }
      }
      else
      {
        tlog_ext(4, "/work/harness.c", 705, "_dns_encode_HTTPS", 0LL, "left len is invalid.");
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
  else
  {
    tlog_ext(4, "/work/harness.c", 694, "_dns_encode_HTTPS", 0LL, "get https param failed.");
    return -1;
  }
}