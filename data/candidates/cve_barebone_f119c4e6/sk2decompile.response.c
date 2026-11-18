int _dns_encode_HTTPS(DNS_PACKET *packet, DNS_SERVICE *svc) {
  int ret = 0;
  unsigned int type = 0;
  unsigned int class = 0;
  char host[256];
  unsigned char *head_ptr = NULL;
  unsigned char *svc_ptr = NULL;
  unsigned char *svc_len_ptr = NULL;
  unsigned int priority = 0;
  unsigned int weight = 0;
  char service[256];
  DNS_HTTPS_SVC_PARM *svc_parm = NULL;
  svc_parm = dns_get_HTTPS_svcparm_start(svc, service, 256, &priority, &weight,
                                         host, 256);
  if (svc_parm == NULL) {
    tlog_ext(4, "/work/harness.c", 694, "_dns_encode_HTTPS", 0,
             "get https param failed.");
    return -1;
  }
  ret = dns_encode_rr_head(packet, service, type, class, priority, 0, &head_ptr);
  if (ret < 0) {
    return -1;
  }
  svc_len_ptr = packet->current;
  if (dns_left_len(packet) < 2) {
    tlog_ext(4, "/work/harness.c", 705, "_dns_encode_HTTPS", 0,
             "left len is invalid.");
    return -1;
  }
  dns_write_short(&packet->current, weight);
  ret = dns_encode_domain(packet, host);
  if (ret < 0) {
    return -1;
  }
  svc_ptr = packet->current;
  while (svc_parm) {
    if ((packet->current - svc_ptr) > svc->svc_len || dns_left_len(packet) < 1) {
      return -1;
    }
    dns_write_short(&packet->current, svc_parm->parm_type);
    dns_write_short(&packet->current, svc_parm->parm_len);
    if (svc_parm->parm_type < 7) {
      memcpy(packet->current, svc_parm->parm_data, svc_parm->parm_len);
      packet->current += svc_parm->parm_len;
    } else {
      packet->current -= 4;
    }
    svc_parm = dns_get_HTTPS_svcparm_next(svc, svc_parm);
  }
  dns_write_short(&head_ptr, packet->current - svc_len_ptr);
  return 0;
}