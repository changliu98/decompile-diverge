int _dns_encode_HTTPS(dns_context *context,dns_rrs *rrs)

{
  int iVar1;
  dns_https_param *param;
  int priority;
  int ttl;
  uchar *rr_start;
  uchar *start;
  uchar *rr_len_ptr;
  char target [256];
  char domain [256];
  int qclass;
  int qtype;
  int ret;
  dns_rrs *rrs_local;
  dns_context *context_local;
  int local_c;
  
  memset(target,0,0x100);
  rr_len_ptr = (uchar *)0x0;
  start = (uchar *)0x0;
  rr_start = (uchar *)0x0;
  ttl = 0;
  priority = 0;
  param = dns_get_HTTPS_svcparm_start(rrs,domain,0x100,&ttl,&priority,target,0x100);
  if (param == (dns_https_param *)0x0) {
    tlog_ext(4,"/work/harness.c",0x2b6,"_dns_encode_HTTPS",(void *)0x0,"get https param failed.");
    local_c = -1;
  }
  else {
    iVar1 = _dns_encode_rr_head(context,domain,0,0,ttl,0,&rr_len_ptr);
    if (iVar1 < 0) {
      local_c = -1;
    }
    else {
      rr_start = context->ptr;
      iVar1 = _dns_left_len(context);
      if (iVar1 < 2) {
        tlog_ext(4,"/work/harness.c",0x2c1,"_dns_encode_HTTPS",(void *)0x0,"left len is invalid.");
        local_c = -1;
      }
      else {
        _dns_write_short(&context->ptr,(unsigned_short)priority);
        iVar1 = _dns_encode_domain(context,target);
        if (iVar1 < 0) {
          local_c = -1;
        }
        else {
          start = context->ptr;
          for (; param != (dns_https_param *)0x0; param = dns_get_HTTPS_svcparm_next(rrs,param)) {
            if (((long)(ulong)rrs->len < (long)context->ptr - (long)start) ||
               (iVar1 = _dns_left_len(context), iVar1 < 1)) {
              return -1;
            }
            _dns_write_short(&context->ptr,param->key);
            _dns_write_short(&context->ptr,param->len);
            if (param->key < 7) {
              memcpy(context->ptr,param + 1,(ulong)param->len);
              context->ptr = context->ptr + (int)(uint)param->len;
            }
            else {
              context->ptr = context->ptr + -4;
            }
          }
          _dns_write_short(&rr_len_ptr,(short)context->ptr - (short)rr_start);
          local_c = 0;
        }
      }
    }
  }
  return local_c;
}