int __cdecl nfs_lookup_reply(uchar *pkt, unsigned int len)
{
  rpc_t rpc_pkt; // [rsp+18h] [rbp-498h] BYREF
  int v6;        // [rsp+4ACh] [rbp-4h]

  // Copy the packet into the local RPC structure
  memcpy(&rpc_pkt, pkt, len);

  uint32_t rpc_call_id = ntohl(rpc_pkt.u.call.id);

  // Check for RPC ID mismatches
  if (rpc_call_id > (unsigned __int64)rpc_id)
    return -1;
  if (rpc_call_id < (unsigned __int64)rpc_id)
    return -124;

  // Check for NFS reply errors
  if (*(_QWORD *)&rpc_pkt.u.reply.rstatus || *(_QWORD *)&rpc_pkt.u.reply.astatus)
  {
    switch (ntohl(rpc_pkt.u.call.proc))
    {
      case 2u:
        if (ntohl(rpc_pkt.u.call.data[0]) != 3)
        {
          puts("*** ERROR: NFS version not supported");
          puts("\n");
          v6 = -1;
        }
        else
        {
          supported_nfs_versions &= ~1u;
          v6 = -2;
        }
        break;

      default:
        v6 = -1;
        break;
    }
  }
  else
  {
    // Success path: Extract file handle based on NFS version
    if ((supported_nfs_versions & 1) != 0)
    {
      // NFSv2 path
      filefh = *(_OWORD *)&rpc_pkt.u.reply.data[1];
      xmmword_40C0 = *(_OWORD *)&rpc_pkt.u.reply.data[5];
    }
    else
    {
      // NFSv3 path
      filefh3_length = ntohl(rpc_pkt.u.reply.data[1]);
      if (filefh3_length > 64)
        filefh3_length = 64;
      memcpy(&filefh, &rpc_pkt.u.reply.data[2], filefh3_length);
    }
    return 0;
  }

  return v6;
}