int __cdecl nfs_lookup_reply(uchar *pkt, unsigned int len)
{
  rpc_t rpc_pkt; // [rsp+18h] [rbp-498h] BYREF
  unsigned int lena; // [rsp+49Ch] [rbp-14h]
  uchar *pkta; // [rsp+4A0h] [rbp-10h]
  int v6; // [rsp+4ACh] [rbp-4h]

  pkta = pkt;
  lena = len;
  memcpy(&rpc_pkt, pkt, len);
  if ( ntohl(rpc_pkt.u.call.id) > (unsigned __int64)rpc_id )
    return -1;
  if ( ntohl(rpc_pkt.u.call.id) < (unsigned __int64)rpc_id )
    return -124;
  if ( *(_QWORD *)&rpc_pkt.u.reply.rstatus || *(_QWORD *)&rpc_pkt.u.reply.astatus )
  {
    switch ( ntohl(rpc_pkt.u.call.proc) )
    {
      case 2u:
        if ( ntohl(rpc_pkt.u.call.data[0]) != 3 )
        {
          puts("*** ERROR: NFS version not supported");
          puts("\n");
          goto LABEL_11;
        }
        supported_nfs_versions &= ~1u;
        v6 = -2;
        break;
      default:
LABEL_11:
        v6 = -1;
        break;
    }
  }
  else
  {
    if ( (supported_nfs_versions & 1) != 0 )
    {
      filefh = *(_OWORD *)&rpc_pkt.u.reply.data[1];
      xmmword_40C0 = *(_OWORD *)&rpc_pkt.u.reply.data[5];
    }
    else
    {
      filefh3_length = ntohl(rpc_pkt.u.reply.data[1]);
      if ( filefh3_length > 64 )
        filefh3_length = 64;
      memcpy(&filefh, &rpc_pkt.u.reply.data[2], filefh3_length);
    }
    return 0;
  }
  return v6;
}