int __cdecl try_read_command_binary(conn *c)
{
  char extbuf[44]; // [rsp+0h] [rbp-50h] BYREF
  uint16_t keylen; // [rsp+30h] [rbp-20h]
  uint8_t extlen; // [rsp+33h] [rbp-1Dh]
  int ii; // [rsp+34h] [rbp-1Ch]
  protocol_binary_request_header *req; // [rsp+38h] [rbp-18h]
  conn *ca; // [rsp+40h] [rbp-10h]

  ca = c;
  if ( (unsigned __int64)c->rbytes >= 0x18 )
  {
    ca->binary_header = *(protocol_binary_request_header *)ca->rcurr;
    req = &ca->binary_header;
    if ( settings_0 > 1 )
    {
      fprintf(stderr, "<%d Read binary protocol data:", (unsigned int)ca->sfd);
      for ( ii = 0; (unsigned __int64)ii < 0x18; ++ii )
      {
        if ( !(ii % 4) )
          fprintf(stderr, "\n<%d   ", (unsigned int)ca->sfd);
        fprintf(stderr, " 0x%02x", *(&req->request.magic + ii));
      }
      fprintf(stderr, "\n");
    }
    ca->binary_header = *req;
    ca->binary_header.request.keylen = ntohs(req->request.keylen);
    ca->binary_header.request.bodylen = ntohl(req->request.bodylen);
    ca->binary_header.request.cas = ntohll(req->request.cas);
    if ( ca->binary_header.request.magic == 128 )
    {
      extlen = ca->binary_header.request.extlen;
      keylen = ca->binary_header.request.keylen;
      if ( ca->rbytes < (unsigned __int64)(extlen + keylen + 24LL) )
        return 0;
      if ( resp_start(ca) )
      {
        ca->cmd = ca->binary_header.request.opcode;
        ca->keylen = ca->binary_header.request.keylen;
        ca->opaque = ca->binary_header.request.opaque;
        ca->cas = 0LL;
        ca->last_cmd_time = current_time;
        memcpy(&extbuf[24], ca->rcurr + 24, extlen);
        ca->rbytes -= keylen + extlen + 24;
        ca->rcurr += keylen + extlen + 24;
        dispatch_bin_command(ca, extbuf);
        return 1;
      }
    }
    else if ( settings_0 )
    {
      fprintf(stderr, "Invalid magic:  %x\n", ca->binary_header.request.magic);
    }
    conn_set_state(ca, conn_states::conn_closing);
    return -1;
  }
  return 0;
}