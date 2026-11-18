int try_read_command_binary(conn *c)

{
  byte bVar1;
  ushort uVar2;
  char *pcVar3;
  _Bool _Var4;
  uint16_t uVar5;
  uint32_t uVar6;
  uint64_t uVar7;
  char extbuf [44];
  uint16_t keylen;
  uint8_t extlen;
  int ii;
  protocol_binary_request_header *req;
  conn *c_local;
  int local_c;
  
  if ((uint)c->rbytes < 0x18) {
    local_c = 0;
  }
  else {
    pcVar3 = c->rcurr;
    *(undefined8 *)&c->binary_header = *(undefined8 *)pcVar3;
    *(undefined8 *)((long)&c->binary_header + 8) = *(undefined8 *)(pcVar3 + 8);
    (c->binary_header).request.cas = *(uint64_t *)(pcVar3 + 0x10);
    if (1 < settings.verbose) {
      fprintf(*(FILE **)PTR_stderr_00103ff8,"<%d Read binary protocol data:",(ulong)(uint)c->sfd);
      for (ii = 0; (uint)ii < 0x18; ii = ii + 1) {
        if (ii % 4 == 0) {
          fprintf(*(FILE **)PTR_stderr_00103ff8,"\n<%d   ",(ulong)(uint)c->sfd);
        }
        fprintf(*(FILE **)PTR_stderr_00103ff8," 0x%02x",(ulong)(c->binary_header).bytes[ii]);
      }
      fprintf(*(FILE **)PTR_stderr_00103ff8,"\n");
    }
    *(undefined8 *)&c->binary_header = *(undefined8 *)&c->binary_header;
    *(undefined8 *)((long)&c->binary_header + 8) = *(undefined8 *)((long)&c->binary_header + 8);
    (c->binary_header).request.cas = (c->binary_header).request.cas;
    uVar5 = ntohs((c->binary_header).request.keylen);
    (c->binary_header).request.keylen = uVar5;
    uVar6 = ntohl((c->binary_header).request.bodylen);
    (c->binary_header).request.bodylen = uVar6;
    uVar7 = ntohll((c->binary_header).request.cas);
    (c->binary_header).request.cas = uVar7;
    if ((c->binary_header).request.magic == 0x80) {
      bVar1 = (c->binary_header).request.extlen;
      uVar2 = (c->binary_header).request.keylen;
      if ((ulong)(long)c->rbytes < (long)(int)((uint)uVar2 + (uint)bVar1) + 0x18U) {
        local_c = 0;
      }
      else {
        _Var4 = resp_start(c);
        if (_Var4) {
          c->cmd = (ushort)(c->binary_header).request.opcode;
          c->keylen = (uint)(c->binary_header).request.keylen;
          c->opaque = (c->binary_header).request.opaque;
          c->cas = 0;
          c->last_cmd_time = current_time;
          memcpy(extbuf + 0x18,c->rcurr + 0x18,(ulong)bVar1);
          c->rbytes = c->rbytes - (bVar1 + 0x18 + (uint)uVar2);
          c->rcurr = c->rcurr + (ulong)bVar1 + 0x18 + (ulong)uVar2;
          dispatch_bin_command(c,extbuf);
          local_c = 1;
        }
        else {
          conn_set_state(c,conn_closing);
          local_c = -1;
        }
      }
    }
    else {
      if (settings.verbose != 0) {
        fprintf(*(FILE **)PTR_stderr_00103ff8,"Invalid magic:  %x\n",
                (ulong)(c->binary_header).request.magic);
      }
      conn_set_state(c,conn_closing);
      local_c = -1;
    }
  }
  return local_c;
}