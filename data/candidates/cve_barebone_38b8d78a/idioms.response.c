int nfs_lookup_reply(void *data, int len)
{
  struct rpc_t rpc;
  int ret;
  int i;
  int *intdata = (int *)data;
  intdata = (int *)data;
  len = (int)len;
  get_rpc(&rpc, data, len);
  if (get_int(rpc.u.call.data[0]) > rpc_id)
    return -1;
  if (get_int(rpc.u.call.data[0]) < rpc_id)
    return -124;
  if (rpc.u.reply.rstatus == 0 && rpc.u.reply.astatus == 0) {
    if (supported_nfs_versions & 1) {
      filefh = rpc.u.reply.data[1];
    }
    else {
      filefh3_length = get_int(rpc.u.reply.data[1]);
      if (filefh3_length > sizeof(filefh3))
        filefh3_length = sizeof(filefh3);
      get_rpc(&filefh,
       rpc.u.reply.data + 2,
       filefh3_length);
    }
    ret = 0;
  }
  else {
    switch (get_int(rpc.u.call.proc)) {
    case 2:
      if (get_int(rpc.u.call.data[1]) == 3) {
        supported_nfs_versions &= ~1;
        ret = -2;
      }
      else {
        print("*** ERROR: NFS version not supported");
        print("\n");
        ret = -1;
      }
      break;
    default:
      ret = -1;
      break;
    }
  }
  return ret;
}