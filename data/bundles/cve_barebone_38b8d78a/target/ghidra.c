int nfs_lookup_reply(uchar *pkt,uint len)

{
  uint32_t uVar1;
  rpc_t rpc_pkt;
  uint len_local;
  uchar *pkt_local;
  int local_c;
  
  memcpy(&rpc_pkt,pkt,(ulong)len);
  uVar1 = ntohl(rpc_pkt.u.call.id);
  if (rpc_id < uVar1) {
    local_c = -1;
  }
  else {
    uVar1 = ntohl(rpc_pkt.u.call.id);
    if (uVar1 < rpc_id) {
      local_c = -0x7c;
    }
    else if ((((rpc_pkt.u.call.rpcvers == 0) && (rpc_pkt.u.call.prog == 0)) &&
             (rpc_pkt.u.call.proc == 0)) && (rpc_pkt.u.reply.data[0] == 0)) {
      if ((supported_nfs_versions & 1U) == 0) {
        filefh3_length = ntohl(rpc_pkt.u.reply.data[1]);
        if (0x40 < filefh3_length) {
          filefh3_length = 0x40;
        }
        memcpy(filefh,(void *)((long)&rpc_pkt.u + 0x20),(long)filefh3_length);
      }
      else {
        filefh[4] = rpc_pkt.u._32_1_;
        filefh[5] = rpc_pkt.u._33_1_;
        filefh[6] = rpc_pkt.u._34_1_;
        filefh[7] = rpc_pkt.u._35_1_;
        filefh[0] = rpc_pkt.u._28_1_;
        filefh[1] = rpc_pkt.u._29_1_;
        filefh[2] = rpc_pkt.u._30_1_;
        filefh[3] = rpc_pkt.u._31_1_;
        filefh[8] = rpc_pkt.u._36_1_;
        filefh[9] = rpc_pkt.u._37_1_;
        filefh[10] = rpc_pkt.u._38_1_;
        filefh[0xb] = rpc_pkt.u._39_1_;
        filefh[0xc] = rpc_pkt.u._40_1_;
        filefh[0xd] = rpc_pkt.u._41_1_;
        filefh[0xe] = rpc_pkt.u._42_1_;
        filefh[0xf] = rpc_pkt.u._43_1_;
        filefh[0x10] = rpc_pkt.u._44_1_;
        filefh[0x11] = rpc_pkt.u._45_1_;
        filefh[0x12] = rpc_pkt.u._46_1_;
        filefh[0x13] = rpc_pkt.u._47_1_;
        filefh[0x14] = rpc_pkt.u._48_1_;
        filefh[0x15] = rpc_pkt.u._49_1_;
        filefh[0x16] = rpc_pkt.u._50_1_;
        filefh[0x17] = rpc_pkt.u._51_1_;
        filefh[0x18] = rpc_pkt.u._52_1_;
        filefh[0x19] = rpc_pkt.u._53_1_;
        filefh[0x1a] = rpc_pkt.u._54_1_;
        filefh[0x1b] = rpc_pkt.u._55_1_;
        filefh[0x1c] = rpc_pkt.u._56_1_;
        filefh[0x1d] = rpc_pkt.u._57_1_;
        filefh[0x1e] = rpc_pkt.u._58_1_;
        filefh[0x1f] = rpc_pkt.u._59_1_;
      }
      local_c = 0;
    }
    else {
      uVar1 = ntohl(rpc_pkt.u.call.proc);
      switch(uVar1) {
      case 0:
        break;
      case 1:
      case 3:
      case 4:
      case 5:
        break;
      case 2:
        uVar1 = ntohl(rpc_pkt.u.reply.data[0]);
        if (uVar1 == 3) {
          supported_nfs_versions = supported_nfs_versions & 0xfe;
          return -2;
        }
        puts("*** ERROR: NFS version not supported");
        puts("\n");
      }
      local_c = -1;
    }
  }
  return local_c;
}