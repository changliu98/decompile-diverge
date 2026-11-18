int nfs_lookup_reply(unsigned char *buf, int len) {
  nfs_lookup_res res;
  memcpy(&res, buf, len);
  if (ntohl(res.common.status) > NFS_OK) return -1;
  if (ntohl(res.common.status) < NFS_OK) return -124;
  if (res.res.data_len == 0 && res.res.attr_len == 0) {
    if (nfs_version & 1) {
      memcpy(nfs_fh, res.res.data + 1, 16);
    } else {
      nfs_fh_len = ntohl(*(unsigned int *)(res.res.data + 1));
      if (nfs_fh_len > 64) nfs_fh_len = 64;
      memcpy(nfs_fh, res.res.data + 2, nfs_fh_len);
    }
    return 0;
  }
  if (ntohl(res.common.error) == 2) {
    if (ntohl(res.common.data[0]) != 3) {
      puts("*** ERROR: NFS version not supported");
      puts("\n");
      return -1;
    }
    nfs_version &= ~1;
    return -2;
  }
  return -1;
}